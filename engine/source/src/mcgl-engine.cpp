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
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] CreateEngine: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] CreateWindow" );
	
	engine->createWindow( width, height, title );
}

void CloseWindow() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] CloseWindow: Engine not created!" );
		return;
	}

	info(*logger, "[MCGL-ENGINE] CloseWindow");
	engine->closeWindow();
}

void Run() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] Run: Engine not created!" );
		return;
	}

	trace( *logger, "[MCGL-ENGINE] Run" );
	engine->run();
}

void Stop() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] Stop: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] Stop" );
	engine->stop();
}

void RegisterBlockType( const chunk::block::Block& block ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RegisterBlockType: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] RegisterBockType" );
	engine->registerBlockType( block );
}

void SetTextures( const std::string& path, UNUM32 textureSize, UNUM32 textureCount ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] SetTextures: Engine not created!" );
		return;
	}

	info(*logger, "[MCGL-ENGINE] SetTextures");

	engine->setTextures( path, textureSize, textureCount );
}

void SetShader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] SetShader: Engine not created!" );
		return;
	}

	info(*logger, "[MCGL-ENGINE] SetShader");

	engine->setShader( vertexShaderPath, fragmentShaderPath );
}

void AddChunk( const chunk::Chunk& chunk ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] AddChunk: Engine not created!" );
		return;
	}

	debug( *logger, "[MCGL-ENGINE] AddChunk" );
	engine->addChunk( chunk );
}

void RemoveChunk( NUM32 x, NUM32 z) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RemoveChunk: Engine not created!" );
		return;
	}

	trace(*logger, "[MCGL-ENGINE] RemoveChunk");
	engine->removeChunk( x, z );
}

void CreateCamera( float x, float y, float z, float pitch, float yaw, float roll ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] CreateCamera: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] CreateCamera" );
	
	engine->createCamera( x, y, z, pitch, yaw, roll );
}

void MoveCamera( float dx, float dy, float dz ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] MoveCamera: Engine not created!" );
		return;
	}

	trace( *logger, "[MCGL-ENGINE] MoveCamera" );
	engine->moveCamera( dx, dy, dz );
}

void RotateCamera( float pitch, float yaw, float roll ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RotateCamera: Engine not created!" );
		return;
	}

	trace( *logger, "[MCGL-ENGINE] RotateCamera" );
	engine->rotateCamera( pitch, yaw, roll );
}

void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RegisterKeyEventCallback: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] RegisterKeyEventCallback" );
	engine->registerKeyEventCallback( callback );
}

void RegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RegisterMouseEventCallback: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] RegisterMouseEventCallback" );
	engine->registerMouseEventCallback( callback );
}

void RegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RegisterStatusEventCallback: Engine not created!" );
		return;
	}
	
	info( *logger, "[MCGL-ENGINE] RegisterStatusEventCallback" );
	engine->registerStatusEventCallback( callback );
}

float GetDeltaTime() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] GetDeltaTime: Engine not created!" );
		return -1.f;
	}

	trace( *logger, "[MCGL-ENGINE] GetDeltaTime" );
	return engine->getDeltaTime();
}

coordinates::WorldCoordinates GetCameraPosition() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] GetCameraPosition: Engine not created!" );
		return { 0, 0, 0 };
	}

	trace( *logger, "[MCGL-ENGINE] GetCameraPosition" );
	return engine->getCameraPosition();
}
