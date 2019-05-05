#pragma once

#include <functional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>

#include "Definition/mcgl_engine_def.h"


typedef std::function<void( NUM32 width, NUM32 height )> MCGL_WINDOW_RESIZE_CALLBACK;

class Window {
public:
	static GLFWwindow* get();

	static void open( UNUM32 width, UNUM32 height, const std::string& title );
	static void close();

	static NUM32 width();
	static NUM32 height();

	static void registerResizeCallback( MCGL_WINDOW_RESIZE_CALLBACK& callback );
	static void deregisterResizeCallback();

private:
	Window() = delete;

	Window( const Window& other ) = delete;
	Window& operator=( const Window& other ) = delete;

	Window( Window&& other ) = delete;
	Window& operator=( Window&& other ) = delete;

	~Window();

	static GLFWwindow* pWindow_;
	static bool isOpen_;

	static NUM32 width_;
	static NUM32 height_;

	static MCGL_WINDOW_RESIZE_CALLBACK callback_;

	static void framebufferSizeCallback( GLFWwindow* window, int width, int height );

};
