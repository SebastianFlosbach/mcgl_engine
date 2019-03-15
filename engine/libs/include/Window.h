#pragma once
#include <glfw/glfw3.h>

#include <string>

class __declspec( dllexport ) Window {
public:
	Window() {
	}

	Window( unsigned int width, unsigned int height, const std::string& title ) : width_( width ), height_( height ) {
		pWindow_ = glfwCreateWindow( width_, height_, title.c_str(), NULL, NULL );
		if ( !pWindow_ ) {
			std::cout << "Failed to create window" << std::endl;
		}
		glfwMakeContextCurrent( pWindow_ );

		//auto func = []( GLFWwindow* window, int width, int height ) {
		//	static_cast<Window*>( glfwGetWindowUserPointer( window ) )->framebufferSizeCallback( window, width, height );
		//};
		//glfwSetFramebufferSizeCallback( pWindow_, func );
	}

	Window( const Window& other ) = delete;
	Window& operator=( const Window& other ) = delete;

	Window( Window&& other ) {
		*this = std::move( other );
	}

	Window& operator=( Window&& other ) {
		this->pWindow_ = other.pWindow_;
		other.pWindow_ = nullptr;
		this->width_ = other.width_;
		this->height_ = other.height_;

		return *this;
	}

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

	void framebufferSizeCallback( GLFWwindow* window, int width, int height ) {
		width_ = width;
		height_ = height;
		glViewport( 0, 0, width, height );
	}
};