#include "mcgl-engine.h"

#include <Engine.h>
#include <Logging/ConsoleLogger.h>
#include <ActionHandling/ThreadedWorkerQueue.h>
#include <ActionHandling/actions.h>
#include <future>

#undef CreateWindow

const std::string loggerName { "mcgl_file_logger" };
const std::string loggerPath { "logs/mcgllog.log" };

std::unique_ptr<ConsoleLogger> logger;
std::unique_ptr<Engine> engine;


bool checkEngine() {
	if( !engine ) {
		return false;
	}

	return true;
}

void CreateEngine() {
	logger = std::make_unique<ConsoleLogger>( /*loggerName, loggerPath*/ );
	info( *logger, "[MCGL-ENGINE] CreateEngine" );

	engine = std::make_unique<Engine>( *logger );
}

void DestroyEngine() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] DestroyEngine: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] DestroyEngine" );
	engine.reset();
}

void CreateWindow( NUM32 width, NUM32 height, const std::string& title ) {
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

	trace( *logger, "[MCGL-ENGINE] Run" );
	engine->run();
}

void Stop() {
	if ( !checkEngine() ) return;

	trace( *logger, "[MCGL-ENGINE] Stop" );
	engine->stop();
}

void RegisterBlockType( const chunk::block::Block& block ) {
	if ( !checkEngine() ) return;

	trace( *logger, "[MCGL-ENGINE] RegisterBockType" );
	engine->registerBlockType( block );
}

void SetTextures( const std::string& path, UNUM32 textureSize, UNUM32 textureCount ) {
	if ( !checkEngine() ) return;

	trace(*logger, "[MCGL-ENGINE] SetTextures");

	engine->setTextures( path, textureSize, textureCount );
}

void SetShader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath ) {
	if ( !checkEngine() ) return;

	trace(*logger, "[MCGL-ENGINE] SetShader");

	engine->setShader( vertexShaderPath, fragmentShaderPath );
}

void AddChunk( const chunk::Chunk& chunk ) {
	if ( !checkEngine() ) return;

	trace( *logger, "[MCGL-ENGINE] AddChunk" );
	engine->addChunk( chunk );
}

void RemoveChunk( NUM32 x, NUM32 z) {
	if (!checkEngine()) return;

	trace(*logger, "[MCGL-ENGINE] RemoveChunk");
	engine->removeChunk( x, z );
}

void CreateCamera( float x, float y, float z, float pitch, float yaw, float roll ) {
	if ( !checkEngine() ) return;

	trace( *logger, "[MCGL-ENGINE] CreateCamera" );
	
	engine->createCamera( x, y, z, pitch, yaw, roll );
}

void MoveCamera( UNUM32 cameraId, float dx, float dy, float dz ) {
	if ( !checkEngine() ) return;

	trace( *logger, "[MCGL-ENGINE] MoveCamera" );
	engine->moveCamera( cameraId, dx, dy, dz );
}

void RotateCamera( UNUM32 cameraId, float pitch, float yaw, float roll ) {
	if ( !checkEngine() ) return;

	trace( *logger, "[MCGL-ENGINE] RotateCamera" );
	engine->rotateCamera( cameraId, pitch, yaw, roll );
}

void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	if ( !checkEngine() ) return;

	trace( *logger, "[MCGL-ENGINE] RegisterKeyEventCallback" );
	engine->registerKeyEventCallback( callback );
}

void RegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {
	if ( !checkEngine() ) return;

	trace( *logger, "[MCGL-ENGINE] RegisterMouseEventCallback" );
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
