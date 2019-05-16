#include "Rendering/Window.h"

#include <iostream>


Window_sptr Window::pInstance_;

Window::~Window() {
	if( pWindow_ ) {
		glfwDestroyWindow( pWindow_ );
	}
}

Window_sptr Window::create() {
	if( !pInstance_ ) {
		pInstance_ = std::shared_ptr<Window>( new Window() );
	}

	return pInstance_;
}

GLFWwindow* Window::get() const {
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

NUM32 Window::width() const {
	return width_;
}

NUM32 Window::height() const {
	return height_;
}

void Window::registerResizeCallback( MCGL_WINDOW_RESIZE_CALLBACK& callback ) {
	callback_ = callback;
}

void Window::deregisterResizeCallback() {
	callback_ = NULL;
}

void Window::framebufferSizeCallback( GLFWwindow* window, int width, int height ) {
	pInstance_->width_ = width;
	pInstance_->height_ = height;
	glViewport( 0, 0, width, height );

	if( pInstance_->callback_ ) {
		pInstance_->callback_( width, height );
	}
}
