#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Definition/mcgl_engine_def.h"
#include "Logging/ILogger.h"
#include "Window.h"
#include "World/Block/BlockLibrary.h"

class Engine {
public:
	Engine( const ILogger& logger );

	Engine( const Engine& other ) = delete;
	Engine& operator=( const Engine& other ) = delete;

	Engine( Engine&& other ) = delete;
	Engine& operator=( Engine&& other ) = delete;

	~Engine() {
		info( logger_, "Destroyed engine" );
		glfwTerminate();
	}

	void createWindow( unsigned int width, unsigned int height, const std::string& title );
	void addBlockType( const world::block::Block& block, unsigned int id );
	void registerKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
	void registerMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );

	void run();

private:
	const ILogger& logger_;

	Window window_;

	world::block::BlockLibrary blockLibrary_{};
};
