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

	void setTextures( const char* texturePath, const NUM32 size, const NUM32 textureCount );
	void setShader( const char* vertexShaderPath, const char* fragmentShaderPath );

	UNUM32 createCamera( const double x, const double y, const double z, const double pitch, const double yaw, const double roll = 0.0 );
	void moveCamera( const UNUM32 cameraId, const double dx, const double dy, const double dz );
	void rotateCamera( const UNUM32 cameraId, const double pitch, const double yaw, const double roll = 0.0 );

	void run();
	void draw();
	void stop();

private:
	void doAction( action::Action_ptr& action );

	void doEngine();
	void doCreateWindow( const action::CreateWindowAction* data );
	void doCloseWindow();
	void doAddBlockType( const action::RegisterBlockTypeAction* data );
	void doRegisterKeyEventCallback( const action::RegisterKeyEventCallbackAction* data );
	void doRegisterMouseEventCallback( const action::RegisterMouseEventCallbackAction* data );
	void doRegisterStatusEventCallback( const action::RegisterStatusEventCallbackAction* data );
	void doAddChunk( const action::AddChunkAction* data );
	void doRemoveChunk( const action::RemoveChunkAction* data );
		 
	void doSetTextures( action::SetTexturesAction* data );
	void doSetShader( action::SetShaderAction* data );

	void doCreateCamera( const action::CreateCameraAction* data );
	void doMoveCamera( const action::MoveCameraAction* data );
	void doRotateCamera( const action::RotateCameraAction* data );

	void doRun();
	void doDraw();
	void doStop();

	const ILogger& logger_;

	std::thread workerThread_;

	ThreadedWorkerQueue<action::Action_ptr> workerQueue_{};
	std::mutex mQueue_{};
	std::condition_variable cvQueue_{};

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

	std::atomic_bool isRunning_ = false;
};
