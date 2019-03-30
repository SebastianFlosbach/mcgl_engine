#include "Window.h"

#include <iostream>

Window::Window( unsigned int width, unsigned int height, const std::string& title ) : width_( width ), height_( height ) {
	pWindow_ = glfwCreateWindow( width_, height_, title.c_str(), NULL, NULL );
	if ( !pWindow_ ) {
		std::cout << "Failed to create window" << std::endl;
	}
	glfwMakeContextCurrent( pWindow_ );

	auto func = []( GLFWwindow* window, int width, int height ) {
		static_cast<Window*>(glfwGetWindowUserPointer( window ))->framebufferSizeCallback( window, width, height );
	};
	glfwSetFramebufferSizeCallback( pWindow_, func );
}

Window::Window( Window&& other ) {
	*this = std::move( other );
}

Window& Window::operator=( Window&& other ) {
	this->pWindow_ = other.pWindow_;
	other.pWindow_ = nullptr;
	this->width_ = other.width_;
	this->height_ = other.height_;

	return *this;
}