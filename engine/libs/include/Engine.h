#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <thread>
#include <iostream>

#include "Window.h"

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

		while ( !glfwWindowShouldClose( window_.get() ) ) {

			glfwSwapBuffers( window_.get() );
			glfwPollEvents();
		}
	}

private:
	Window window_;

};
