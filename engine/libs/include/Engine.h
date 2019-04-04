#pragma once
#include "Definition/mcgl_engine_def.h"
#include "Logging/ILogger.h"
#include "Window.h"
#include "World/Block/BlockLibrary.h"
#include "World/Chunk/Chunk.h"
#include "World/World.h"
#include "Renderer/Renderer.h"
#include "Camera.h"

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
	void closeWindow();
	void addBlockType( const world::block::Block& block, unsigned int id );
	void registerKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
	void registerMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
	void registerStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );
	void addChunk( int x, int z, const world::chunk::Chunk& chunk );
	//void removeChunk( unsigned int x, unsigned int z );

	void setTextures( texture::TextureAtlas&& textureAtlas );
	void setShader( Shader&& shader );

	unsigned int createCamera( const double x, const double y, const double z, const double pitch, const double yaw, const double roll = 0.0 );
	void moveCamera( const unsigned int cameraId, const double dx, const double dy, const double dz );
	void rotateCamera( const unsigned int cameraId, const double pitch, const double yaw, const double roll = 0.0 );

	inline float getDeltaTime() {
		return deltaTime_;
	}

	void run();
	void stop();

private:
	const ILogger& logger_;

	Window window_;

	world::block::BlockLibrary blockLibrary_{};
	world::World world_ {};
	std::unique_ptr<Renderer> renderer_;
	Camera camera_;

	MCGL_STATUS_EVENT_CALLBACK statusCallback_;
	inline void invokeStatusCallback( const StatusEvent& statusEvent ) {
		if ( statusCallback_ ) {
			statusCallback_( statusEvent );
		}
	}

	float deltaTime_ = 0.0f;
	float lastFrame_ = 0.0f;

	bool isRunning_ = false;
};
