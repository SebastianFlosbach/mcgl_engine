#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <thread>
#include <iostream>

#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "CubeMap.h"
#include "Mesh/Mesh.h"
#include "World/Chunk/Chunk.h"
#include "World/Chunk/ChunkMeshBuilder.h"

#define ASSERT(x) if(x) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT( GLCheckError() );

static void GLClearError() {
	while ( glGetError() != GL_NO_ERROR );
}

static bool GLCheckError() {
	bool hasError = false;

	while ( GLenum error = glGetError() ) {
		std::cout << "[OpenGL Error]: " << error << std::endl;
		hasError = true;
	}

	return hasError;
}

static void errorCallback( int id, const char* message ) {
	std::cout << "GLFW Error: [" << id << "] " << message << std::endl;
}

static Camera camera;
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

static void processInput( GLFWwindow *window ) {
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) {
		glfwSetWindowShouldClose( window, true );
	}

	float cameraSpeed = 2.5f * deltaTime;
	if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS ) {
		camera.move( 0.0f, 0.0f, cameraSpeed );
	}
	if ( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS ) {
		camera.move( 0.0f, 0.0f, -cameraSpeed );
	}
	if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS ) {
		camera.move( -cameraSpeed, 0.0f, 0.0f );
	}
	if ( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS ) {
		camera.move( cameraSpeed, 0.0f, 0.0f );
	}
}

bool firstMouse = true;
float lastX = 400;
float lastY = 300;

static void mouse_callback( GLFWwindow* window, double xpos, double ypos ) {
	if ( firstMouse ) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.rotateD( yoffset, xoffset );
}

class Engine {
public:
	Engine() {
	}

	Engine( const Engine& other ) = delete;
	Engine& operator=( const Engine& other ) = delete;

	Engine( Engine&& other ) {
		*this = std::move( other );
	}

	Engine& operator=( Engine&& other ) {
		this->window_ = std::move( other.window_ );

		return *this;
	}

	void init() {
		if ( !glfwInit() ) {
			throw std::runtime_error( "Could not initialize GLFW!" );
		}
		glfwSetErrorCallback( errorCallback );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	}

	~Engine() {
		glfwTerminate();
	}

	void createWindow( unsigned int width, unsigned int height, const std::string& title ) {
		window_ = Window( width, height, title );
	}

	void run() {
		if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glViewport( 0, 0, window_.width(), window_.height() );

		world::chunk::Chunk chunk{};
		world::block::Block block{ false };
		chunk.setBlock( block, 0, 0, 0 );
		chunk.setBlock( block, 0, 0, 1 );
		chunk.setBlock( block, 1, 0, 0 );
		chunk.setBlock( block, 1, 0, 1 );
		chunk.setBlock( block, 0, 1, 0 );
		chunk.setBlock( block, 0, 1, 1 );
		chunk.setBlock( block, 1, 1, 0 );
		chunk.setBlock( block, 1, 1, 1 );

		world::chunk::ChunkMeshBuilder cmb = world::chunk::ChunkMeshBuilder();

		Texture blockTexture( "../resources/textures/container.jpg" );

		Mesh blockMesh = std::move( cmb.createChunkMesh( chunk, blockTexture ) );

		Shader blockShader = Shader();
		blockShader.addVertexShader( "../resources/shaders/vertexShader" );
		blockShader.addFragmentShader( "../resources/shaders/fragmentShader" );
		blockShader.compile();
		blockShader.use();

		glfwSetInputMode( window_.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );
		glfwSetCursorPosCallback( window_.get(), mouse_callback );

		glEnable( GL_DEPTH_TEST );

		camera = Camera( 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, -1.0f );

		glm::mat4 model( 1.0f );
		glm::mat4 projection = glm::perspective( glm::radians( 45.0f ), (float)window_.width() / (float)window_.height(), 0.1f, 100.0f );

		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		while ( !glfwWindowShouldClose( window_.get() ) ) {

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Input
			processInput( window_.get() );

			// Rendering
			glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			blockShader.use();

			blockShader.setUniformMat4f( "model", model );
			blockShader.setUniformMat4f( "view", camera.getView() );
			blockShader.setUniformMat4f( "projection", projection );
			
			blockMesh.Draw( blockShader );

			glfwSwapBuffers( window_.get() );
			glfwPollEvents();
		}
	}

private:
	Window window_;

};
