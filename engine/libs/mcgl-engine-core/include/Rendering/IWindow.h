#pragma once

#include <functional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <memory>
#include <string>

#include "Definition/mcgl_engine_def.h"


typedef std::function<void( NUM32 width, NUM32 height )> MCGL_WINDOW_RESIZE_CALLBACK;


class IWindow {
public:
	virtual ~IWindow() = default;

	virtual GLFWwindow* get() const = 0;

	virtual void open( UNUM32 width, UNUM32 height, const std::string& title ) = 0;
	virtual void close() = 0;

	virtual NUM32 width() const = 0;
	virtual NUM32 height() const = 0;

	virtual void registerResizeCallback( MCGL_WINDOW_RESIZE_CALLBACK& callback ) = 0;
	virtual void deregisterResizeCallback() = 0;

};

typedef std::shared_ptr<IWindow> IWindow_sptr;
