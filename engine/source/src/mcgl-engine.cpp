#include "mcgl-engine.h"

#include <Engine.h>
#include <Logging/SpdFileLogger.h>
#include <ActionHandling/ThreadedWorkerQueue.h>
#include <ActionHandling/actions.h>
#include <future>


const std::string loggerName { "mcgl_file_logger" };
const std::string loggerPath { "logs/mcgllog.log" };

std::unique_ptr<logging::SpdFileLogger> logger;
std::unique_ptr<Engine> engine;


void MCGLCreateEngine() {
	logger = std::make_unique<logging::SpdFileLogger>( loggerName, loggerPath );
	info( *logger, "[MCGL-ENGINE] CreateEngine" );

	engine = std::make_unique<Engine>( *logger );
}

void MCGLDestroyEngine() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] DestroyEngine: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] DestroyEngine" );
	engine->destroy();
	engine.reset();
}

void MCGLCreateWindow( NUM32 width, NUM32 height, const std::string& title ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] CreateEngine: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] CreateWindow" );
	
	engine->createWindow( width, height, title );
}

void MCGLCloseWindow() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] CloseWindow: Engine not created!" );
		return;
	}

	info(*logger, "[MCGL-ENGINE] CloseWindow");
	engine->closeWindow();
}

void MCGLRun() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] Run: Engine not created!" );
		return;
	}

	trace( *logger, "[MCGL-ENGINE] Run" );
	engine->run();
}

void MCGLStop() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] Stop: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] Stop" );
	engine->stop();
}

void MCGLRegisterBlockType( const chunk::block::Block& block ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RegisterBlockType: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] RegisterBockType" );
	engine->registerBlockType( block );
}

void MCGLSetTextures( const std::string& path, UNUM32 textureSize, UNUM32 textureCount ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] SetTextures: Engine not created!" );
		return;
	}

	info(*logger, "[MCGL-ENGINE] SetTextures");

	engine->setTextures( path, textureSize, textureCount );
}

void MCGLSetSkyboxTextures(
	const std::string& right,
	const std::string& left,
	const std::string& top,
	const std::string& bottom,
	const std::string& front,
	const std::string& back
) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] SetSkyboxTextures: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] SetSkyboxTextures" );

	engine->setSkyboxTexture(
		right,
		left,
		top,
		bottom,
		front,
		back
	);
}

void MCGLSetShader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] SetShader: Engine not created!" );
		return;
	}

	info(*logger, "[MCGL-ENGINE] SetShader");

	engine->setShader( vertexShaderPath, fragmentShaderPath );
}

void MCGLAddChunk( const chunk::Chunk& chunk ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] AddChunk: Engine not created!" );
		return;
	}

	debug( *logger, "[MCGL-ENGINE] AddChunk" );
	engine->addChunk( chunk );
}

void MCGLRemoveChunk( NUM32 x, NUM32 z) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RemoveChunk: Engine not created!" );
		return;
	}

	trace(*logger, "[MCGL-ENGINE] RemoveChunk");
	engine->removeChunk( x, z );
}

void MCGLCreateCamera( float x, float y, float z, float pitch, float yaw, float roll ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] CreateCamera: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] CreateCamera" );
	
	engine->createCamera( x, y, z, pitch, yaw, roll );
}

void MCGLMoveCamera( float dx, float dy, float dz ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] MoveCamera: Engine not created!" );
		return;
	}

	trace( *logger, "[MCGL-ENGINE] MoveCamera" );
	engine->moveCamera( dx, dy, dz );
}

void MCGLRotateCamera( float pitch, float yaw, float roll ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RotateCamera: Engine not created!" );
		return;
	}

	trace( *logger, "[MCGL-ENGINE] RotateCamera" );
	engine->rotateCamera( pitch, yaw, roll );
}

void MCGLRegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RegisterKeyEventCallback: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] RegisterKeyEventCallback" );
	engine->registerKeyEventCallback( callback );
}

void MCGLRegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RegisterMouseEventCallback: Engine not created!" );
		return;
	}

	info( *logger, "[MCGL-ENGINE] RegisterMouseEventCallback" );
	engine->registerMouseEventCallback( callback );
}

void MCGLRegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback ) {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] RegisterStatusEventCallback: Engine not created!" );
		return;
	}
	
	info( *logger, "[MCGL-ENGINE] RegisterStatusEventCallback" );
	engine->registerStatusEventCallback( callback );
}

coordinates::WorldCoordinates MCGLGetCameraPosition() {
	if( !engine ) {
		error( *logger, "[MCGL-ENGINE] GetCameraPosition: Engine not created!" );
		return { 0, 0, 0 };
	}

	trace( *logger, "[MCGL-ENGINE] GetCameraPosition" );
	return engine->getCameraPosition();
}
