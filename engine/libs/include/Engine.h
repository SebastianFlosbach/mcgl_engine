#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <thread>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "World/Block/BlockLibrary.h"
#include "Definition/mcgl_engine_def.h"
#include "Eventing/KeyEventHandler.h"
#include "Eventing/MouseEventHandler.h"
#include "Logging/ILogger.h"


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


class Engine {
public:
	Engine( const ILogger& logger ) : logger_( logger ) {
		info( logger_, "Initialize engine" );
		if ( !glfwInit() ) {
			throw std::runtime_error( "Could not initialize GLFW!" );
		}
		glfwSetErrorCallback( errorCallback );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	}

	Engine( const Engine& other ) = delete;
	Engine& operator=( const Engine& other ) = delete;

	Engine( Engine&& other ) = delete;
	Engine& operator=( Engine&& other ) = delete;

	~Engine() {
		info( logger_, "Destroyed engine" );
		glfwTerminate();
	}

	void createWindow( unsigned int width, unsigned int height, const std::string& title ) {
		info( logger_, "createWindow()" );

		window_ = Window( width, height, title );
	}

	void addBlockType( const world::block::Block& block, unsigned int id ) {
		info( logger_, "addBlockType()" );

		blockLibrary_.addBlock( block, id );
	}

	void registerKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
		info( logger_, "registerKeyEventCallback" );

		KeyEventHandler::registerCallback( window_.get(), callback );
	}

	void registerMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {
		info( logger_, "registerMouseEventCallback" );

		MouseEventHandler::registerCallback( window_.get(), callback );
	}

	void run() {
		info( logger_, "run()" );

		if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glViewport( 0, 0, window_.width(), window_.height() );

		//glfwSetInputMode( window_.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );

		glEnable( GL_DEPTH_TEST );


		glm::mat4 model( 1.0f );
		model = glm::scale( model, { 0.2f, 0.2f, 0.2f } );

		glm::mat4 projection = glm::perspective( glm::radians( 45.0f ), (float)window_.width() / (float)window_.height(), 0.1f, 100.0f );

		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		while ( !glfwWindowShouldClose( window_.get() ) ) {
			// Rendering
			glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			glfwSwapBuffers( window_.get() );
			glfwPollEvents();
		}
	}

private:
	const ILogger& logger_;

	Window window_;

	world::block::BlockLibrary blockLibrary_{};
};
