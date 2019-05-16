#pragma once

#include "Rendering/IWindow.h"

class Window;

typedef std::shared_ptr<Window> Window_sptr;

class Window : public IWindow {
public:

	virtual ~Window() override;

	static Window_sptr create();

	virtual GLFWwindow* get() const override;

	virtual void open( UNUM32 width, UNUM32 height, const std::string& title ) override;
	virtual void close() override;

	virtual NUM32 width() const override;
	virtual NUM32 height() const override;

	virtual void registerResizeCallback( MCGL_WINDOW_RESIZE_CALLBACK& callback ) override;
	virtual void deregisterResizeCallback() override;

private:
	Window() = default;

	Window( const Window& other ) = delete;
	Window& operator=( const Window& other ) = delete;

	Window( Window&& other ) = delete;
	Window& operator=( Window&& other ) = delete;


	GLFWwindow* pWindow_;
	bool isOpen_;

	NUM32 width_;
	NUM32 height_;

	MCGL_WINDOW_RESIZE_CALLBACK callback_;

	static Window_sptr pInstance_;
	static void framebufferSizeCallback( GLFWwindow* window, int width, int height );

};
