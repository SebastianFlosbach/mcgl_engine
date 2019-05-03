#pragma once

#include "Definition/mcgl_engine_def.h"
#include "Logging/ILogger.h"
#include "Window.h"
#include "Chunk/Block/BlockLibrary.h"
#include "Chunk/Chunk.h"
#include "World/World.h"
#include "Renderer/Renderer.h"
#include "Camera.h"
#include "ActionHandling/ThreadedWorkerQueue.h"
#include "ActionHandling/actions.h"
#include "Chunk/ChunkCollection.h"
#include "Chunk/Builder/ThreadedChunkMeshBuilder.h"


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

	coordinates::WorldCoordinates getCameraPosition( UNUM32 cameraId ) const {
		return camera_.getPosition();
	}

	void createWindow( const UNUM32 width, const UNUM32 height, const std::string& title );
	void closeWindow();
	void registerBlockType( const chunk::block::Block& block );
	void registerKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
	void registerMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
	void registerStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );
	void addChunk( const chunk::Chunk& chunk );
	void removeChunk( const UNUM32 x, const UNUM32 z );

	void setTextures( const char* texturePath, const NUM32 size, const NUM32 textureCount );
	void setShader( const char* vertexShaderPath, const char* fragmentShaderPath );

	UNUM32 createCamera( const double x, const double y, const double z, const double pitch, const double yaw, const double roll = 0.0 );
	void moveCamera( const UNUM32 cameraId, const double dx, const double dy, const double dz );
	void rotateCamera( const UNUM32 cameraId, const double pitch, const double yaw, const double roll = 0.0 );

	void run();
	void stop();

private:
	void addMesh( const coordinates::WorldCoordinates& position, mesh::Mesh* mesh );
	void doAddMesh( action::AddMeshAction* data );

	void doAction( action::Action_ptr& action );

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

	const ILogger& logger_;

	std::thread workerThread_;

	ThreadedWorkerQueue<action::Action_ptr> workerQueue_{};
	std::mutex mQueue_{};
	std::condition_variable cvQueue_{};

	Window window_;

	std::unique_ptr<Renderer> pRenderer_;

	chunk::block::BlockLibrary_sptr					pBlockLibrary_;	
	chunk::ChunkCollection_ptr						pChunks_;
	world::World_ptr								pWorld_;
	chunk::builder::ThreadedChunkMeshBuilder_ptr	pChunkMeshBuilder_;

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
