#pragma once
#include "Definition/mcgl_engine_def.h"
#include "Logging/ILogger.h"
#include "Window.h"
#include "World/Block/BlockLibrary.h"
#include "World/Chunk/Chunk.h"
#include "World/World.h"
#include "Renderer/Renderer.h"
#include "Camera.h"
#include "ActionHandling/ThreadedWorkerQueue.h"
#include "ActionHandling/actions.h"

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

	inline float getDeltaTime() {
		return deltaTime_;
	}

	void createWindow( const UNUM32 width, const UNUM32 height, const std::string& title );
	void closeWindow();
	void addBlockType( const world::block::Block& block, UNUM32 id );
	void registerKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
	void registerMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
	void registerStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );
	void addChunk( const NUM32 x, const NUM32 z, const world::chunk::Chunk& chunk );
	void removeChunk( const UNUM32 x, const UNUM32 z );

	void setTextures( texture::TextureAtlas&& textureAtlas );
	void setShader( Shader&& shader );

	UNUM32 createCamera( const double x, const double y, const double z, const double pitch, const double yaw, const double roll = 0.0 );
	void moveCamera( const UNUM32 cameraId, const double dx, const double dy, const double dz );
	void rotateCamera( const UNUM32 cameraId, const double pitch, const double yaw, const double roll = 0.0 );

	void run();
	void stop();

private:
	void doCreateWindow( const UNUM32 width, const UNUM32 height, const std::string& title );
	void doCloseWindow();
	void doAddBlockType( const world::block::Block& block, UNUM32 id );
	void doRegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
	void doRegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
	void doRegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );
	void doAddChunk( const NUM32 x, const NUM32 z, const world::chunk::Chunk& chunk);
	void doRemoveChunk( const UNUM32 x, const UNUM32 z );
		 
	void doSetTextures( texture::TextureAtlas&& textureAtlas );
	void doSetShader( Shader&& shader );

	UNUM32 doCreateCamera( const double x, const double y, const double z, const double pitch, const double yaw, const double roll = 0.0 );
	void doMoveCamera( const UNUM32 cameraId, const double dx, const double dy, const double dz );
	void doRotateCamera( const UNUM32 cameraId, const double pitch, const double yaw, const double roll = 0.0 );

	void doRun();
	void doStop();

	const ILogger& logger_;

	ThreadedWorkerQueue<action::Action> workerQueue_{};

	Window window_;

	world::block::BlockLibrary blockLibrary_{};
	world::World world_{};
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
