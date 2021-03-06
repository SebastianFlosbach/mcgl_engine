#pragma once

#include "Definition/mcgl_engine_def.h"
#include "Logging/ILogger.h"
#include "Rendering/Window.h"
#include "Chunk/Chunk.h"
#include "Rendering/Renderer.h"
#include "Camera.h"
#include "ActionHandling/ThreadedWorkerQueue.h"
#include "ActionHandling/actions.h"
#include "Chunk/Builder/ThreadedChunkMeshBuilder.h"
#include "AssetManager.h"


class Engine {
public:
	Engine( const ILogger& logger );

	Engine( const Engine& other ) = delete;
	Engine& operator=( const Engine& other ) = delete;

	Engine( Engine&& other ) = delete;
	Engine& operator=( Engine&& other ) = delete;

	~Engine();

	inline float getDeltaTime() {
		return deltaTime_;
	}

	coordinates::WorldCoordinates getCameraPosition() const {
		return camera_.getPosition();
	}

	void createWindow( UNUM32 width, UNUM32 height, const std::string& title );
	void closeWindow();

	void registerBlockType( const chunk::block::Block& block );
	void addChunk( const chunk::Chunk& chunk );
	void removeChunk( const UNUM32 x, const UNUM32 z );

	void registerKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
	void registerMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
	void registerStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );

	void setTextures( const std::string& texturePath, NUM32 size, NUM32 textureCount );
	void setShader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath );

	UNUM32 createCamera( double x, double y, double z, double pitch, double yaw, double roll = 0.0 );
	void moveCamera( double dx, double dy, double dz );
	void rotateCamera( double pitch, double yaw, double roll = 0.0 );

	void run();
	void stop();

	void destroy();

private:
	void addMesh( const coordinates::WorldCoordinates& position, mesh::Mesh* mesh );
	void doAddMesh( action::AddMeshAction* data );

	void doAction( action::Action* action );

	void doEngine();
	void doCreateWindow( action::CreateWindowAction* data );
	void doCloseWindow();
	void doRegisterBlockType( action::RegisterBlockTypeAction* data );
	void doRegisterKeyEventCallback( action::RegisterKeyEventCallbackAction* data );
	void doRegisterMouseEventCallback( action::RegisterMouseEventCallbackAction* data );
	void doRegisterStatusEventCallback( action::RegisterStatusEventCallbackAction* data );
	void doAddChunk( action::AddChunkAction* data );
	void doRemoveChunk( action::RemoveChunkAction* data );
		 
	void doSetTextures( action::SetTexturesAction* data );
	void doSetShader( action::SetShaderAction* data );

	void doCreateCamera( action::CreateCameraAction* data );
	void doMoveCamera( action::MoveCameraAction* data );
	void doRotateCamera( action::RotateCameraAction* data );

	void doDraw();
	void doStop();

	void doDestroy();

	const ILogger& logger_;

	ThreadedWorkerQueue<action::Action_ptr> workerQueue_{};

	IWindow_sptr pWindow_;

	AssetManager_ptr pAssetManager_;
	
	Camera camera_;

	MCGL_STATUS_EVENT_CALLBACK statusCallback_;
	inline void invokeStatusCallback( const eventing::StatusEvent& statusEvent ) {
		if ( statusCallback_ ) {
			statusCallback_( statusEvent );
		}
	}

	float deltaTime_ = 0.0f;
	float lastFrame_ = 0.0f;

	std::atomic_bool isRunning_ = false;

	std::condition_variable cvDestroy_{};
	std::mutex mEngine_{};
	std::atomic_bool isDestroyed_ = false;
};
