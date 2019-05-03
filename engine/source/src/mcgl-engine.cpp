#include "mcgl-engine.h"

#include <Engine.h>
#include <Logging/SpdFileLogger.h>
#include <ActionHandling/ThreadedWorkerQueue.h>
#include <ActionHandling/actions.h>
#include <future>

#undef CreateWindow

const std::string loggerName { "mcgl_file_logger" };
const std::string loggerPath { "logs/mcgllog.log" };

std::unique_ptr<SpdFileLogger> logger;
std::unique_ptr<Engine> engine;


inline bool checkEngine() {
	if ( !engine ) {
		error( *logger, "Engine was not created!" );
		return false;
	}

	return true;
}

void CreateEngine() {
	logger = std::make_unique<SpdFileLogger>( loggerName, loggerPath );
	info( *logger, "[MCGL-ENGINE] CreateEngine" );

	engine = std::make_unique<Engine>( *logger );
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

	info(*logger, "[MCGL-ENGINE] CloseWindow");
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

void RegisterBlockType( const chunk::block::Block& block ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RegisterBockType" );
	engine->registerBlockType( block );
}

void SetTextures( const char* path, const UNUM32 textureSize, const UNUM32 textureCount ) {
	if ( !checkEngine() ) return;

	info(*logger, "[MCGL-ENGINE] SetTextures");

	engine->setTextures( path, textureSize, textureCount );
}

void SetShader( const char* vertexShaderPath, const char* fragmentShaderPath ) {
	if ( !checkEngine() ) return;

	info(*logger, "[MCGL-ENGINE] SetShader");

	engine->setShader( vertexShaderPath, fragmentShaderPath );
}

void AddChunk( const chunk::Chunk& chunk ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] AddChunk" );
	engine->addChunk( chunk );
}

void RemoveChunk(const NUM32 x, const NUM32 z) {
	if (!checkEngine()) return;

	info(*logger, "[MCGL-ENGINE] RemoveChunk");
	engine->removeChunk( x, z );
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

void Set( MCGL_CONFIG config, void* data ) {
	throw std::runtime_error( "Not implemented" );
}

float GetDeltaTime() {
	if ( !checkEngine() ) return -1.0f;

	return engine->getDeltaTime();
}

coordinates::WorldCoordinates GetCameraPosition( UNUM32 cameraId ) {
	if( !checkEngine() ) return { 0, 0, 0 };

	return engine->getCameraPosition( cameraId );
}
