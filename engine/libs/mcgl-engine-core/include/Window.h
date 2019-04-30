#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string>

class Window {
public:
	Window() {}
	Window( unsigned int width, unsigned int height, const std::string& title );

	Window( const Window& other ) = delete;
	Window& operator=( const Window& other ) = delete;

	Window( Window&& other );
	Window& operator=( Window&& other );

	~Window() {
		if ( pWindow_ ) {
			glfwDestroyWindow( pWindow_ );
		}
	}

	operator bool() const {
		return pWindow_ != nullptr;
	}

	GLFWwindow* get() {
		return pWindow_;
	}

	void close() {
		if ( pWindow_ ) {
			glfwDestroyWindow( pWindow_ );
			pWindow_ = nullptr;
		}
	}

	// TODO: Get width and height from pWindow_
	unsigned int width() {
		return width_;
	}

	unsigned int height() {
		return height_;
	}

private:
	GLFWwindow* pWindow_ = nullptr;

	unsigned int width_ = 800;
	unsigned int height_ = 600;

	static void framebufferSizeCallback( GLFWwindow* window, int width, int height ) {
		glViewport( 0, 0, width, height );
	}
};