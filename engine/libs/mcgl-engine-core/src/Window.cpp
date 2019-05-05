#include "Window.h"

#include <iostream>


Window::~Window() {
	if( pWindow_ ) {
		glfwDestroyWindow( pWindow_ );
	}
}

GLFWwindow* Window::pWindow_{ nullptr };
bool Window::isOpen_{ false };

NUM32 Window::width_{ 800 };
NUM32 Window::height_{ 600 };

MCGL_WINDOW_RESIZE_CALLBACK Window::callback_{ NULL };

GLFWwindow* Window::get() {
	return pWindow_;
}

void Window::open( UNUM32 width, UNUM32 height, const std::string& title ) {
	if( isOpen_ ) {
		return;
	}
	isOpen_ = true;

	width_ = width;
	height_ = height;
	pWindow_ = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );
	if( !pWindow_ ) {
		std::cout << "Failed to create window" << std::endl;
	}
	glfwMakeContextCurrent( pWindow_ );

	glfwSetFramebufferSizeCallback( pWindow_, framebufferSizeCallback );

}

void Window::close() {
	if( !isOpen_ ) {
		return;
	}
	isOpen_ = false;

	if( pWindow_ ) {
		glfwDestroyWindow( pWindow_ );
		pWindow_ = nullptr;
	}

}

NUM32 Window::width() {
	return width_;
}

NUM32 Window::height() {
	return height_;
}

void Window::registerResizeCallback( MCGL_WINDOW_RESIZE_CALLBACK& callback ) {
	callback_ = callback;
}

void Window::deregisterResizeCallback() {
	callback_ = NULL;
}

void Window::framebufferSizeCallback( GLFWwindow* window, int width, int height ) {
	width_ = width;
	height_ = height;
	glViewport( 0, 0, width, height );

	if( callback_ ) {
		callback_( width, height );
	}
}
