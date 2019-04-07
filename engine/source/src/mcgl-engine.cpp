#include "mcgl-engine.h"

#include <Engine.h>
#include <Logging/SpdFileLogger.h>
#include <ActionHandling/ThreadedWorkerQueue.h>
#include <ActionHandling/Action/Action.h>

#undef CreateWindow

const std::string loggerName { "mcgl_file_logger" };
const std::string loggerPath { "logs/mcgllog.log" };

std::mutex mEngine;

std::atomic_bool isRunning = false;

std::unique_ptr<ThreadedWorkerQueue<action::Action*>> engineThread_;

std::unique_ptr<SpdFileLogger> logger;
std::unique_ptr<Engine> engine;


inline bool checkEngine() {
	if ( !engine ) {
		error( *logger, "Engine was not created!" );
		return false;
	}

	return true;
}

void doAction( action::Action* action ) {

}

void CreateEngine() {
	if ( isRunning.exchange( true ) ) {
		return;
	}

	logger = std::make_unique<SpdFileLogger>( loggerName, loggerPath );
	info( *logger, "[MCGL-ENGINE] CreateEngine" );

	engineThread_ = std::make_unique<ThreadedWorkerQueue<action::Action*>>();
	engineThread_->start( doAction );
	
}

void DestroyEngine() {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] DestroyEngine" );
	engine.reset();
}

void CreateWindow( const NUM32 width, const NUM32 height, const std::string& title ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] CreateWindow" );
	engine->createWindow( width, height, title );
}

void CloseWindow() {
	if ( !checkEngine() ) return;

	engine->closeWindow();
}

void Run() {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] Run" );
	engine->run();
}

void Stop() {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] Stop" );
	engine->stop();
}

void RegisterBlockType( const world::block::Block& block, const NUM32 id ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RegisterBockType" );
	engine->addBlockType( block, id );
}

void SetTextures( const char* path, const UNUM32 textureSize, const UNUM32 textureCount ) {
	if ( !checkEngine() ) return;

	texture::TextureAtlas textureAtlas( path, textureSize, textureCount );

	engine->setTextures( std::move( textureAtlas ) );
}

void SetShader( const char* vertexShaderPath, const char* fragmentShaderPath ) {
	if ( !checkEngine() ) return;

	Shader shader = Shader();
	shader.addVertexShader( vertexShaderPath );
	shader.addFragmentShader( fragmentShaderPath );
	shader.compile();

	engine->setShader( std::move( shader ) );
}


void AddChunk( const UNUM32 x, const UNUM32 z, const world::chunk::Chunk& chunk ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] AddChunk" );
	engine->addChunk( x, z, chunk );
}

UNUM32 CreateCamera( const double x, const double y, const double z, const double pitch, const double yaw, const double roll ) {
	if ( !checkEngine() ) return 0;

	info( *logger, "[MCGL-ENGINE] CreateCamera" );
	return engine->createCamera( x, y, z, pitch, yaw, roll );
}

void MoveCamera( const UNUM32 cameraId, const double dx, const double dy, const double dz ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] MoveCamera" );
	engine->moveCamera( cameraId, dx, dy, dz );
}

void RotateCamera( const UNUM32 cameraId, const double pitch, const double yaw, const double roll ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RotateCamera" );
	engine->rotateCamera( cameraId, pitch, yaw, roll );
}


void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RegisterKeyEventCallback" );
	engine->registerKeyEventCallback( callback );
}

void RegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RegisterMouseEventCallback" );
	engine->registerMouseEventCallback( callback );
}

void RegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback ) {
	engine->registerStatusEventCallback( callback );
}

float GetDeltaTime() {
	if ( !checkEngine() ) return -1.0f;

	return engine->getDeltaTime();
}
