#pragma once

#include <iostream>

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