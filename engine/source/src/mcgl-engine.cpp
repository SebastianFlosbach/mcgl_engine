#include "mcgl-engine.h"

#include <Engine.h>
#include <Logging/SpdFileLogger.h>
#include <ActionHandling/ThreadedWorkerQueue.h>
#include <ActionHandling/actions.h>

#undef CreateWindow

const std::string loggerName { "mcgl_file_logger" };
const std::string loggerPath { "logs/mcgllog.log" };


std::atomic_bool isRunning = false;

std::unique_ptr<SpdFileLogger> logger;

ThreadedWorkerQueue<action::Action_ptr> engineThread;

std::unique_ptr<Engine> engine;


inline bool checkEngine() {
	if ( !engine ) {
		error( *logger, "Engine was not created!" );
		return false;
	}

	return true;
}

void doAction( const action::Action_ptr& action ) {
	switch ( action->type() ) {
	case action::ActionType::CreateWindowAction:
	{
		auto* data = static_cast<action::CreateWindowAction*>(action.get());
		engine->createWindow( data->width_, data->height_, data->title_ );
	}
		break;
	case action::ActionType::RunAction:
	{
		engine->run();
	}
		break;
	case action::ActionType::StopAction:
	{
		engine->stop();
	}
		break;
	case action::ActionType::SetShaderAction:
	{
		auto* data = static_cast<action::SetShaderData*>(action.get());

		Shader shader = Shader();
		shader.addVertexShader( data->vertexPath_ );
		shader.addFragmentShader( data->fragmentPath_ );
		shader.compile();

		engine->setShader( std::move( shader ) );
	}
		break;
	default:
		break;
	}
}

void CreateEngine() {
	if ( isRunning.exchange( true ) ) {
		return;
	}

	logger = std::make_unique<SpdFileLogger>( loggerName, loggerPath );
	info( *logger, "[MCGL-ENGINE] CreateEngine" );

	engine = std::make_unique<Engine>( *logger );

	engineThread = ThreadedWorkerQueue<action::Action_ptr>();
	engineThread.start( doAction );
}

void DestroyEngine() {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] DestroyEngine" );
	engine.reset();
}

void CreateWindow( const NUM32 width, const NUM32 height, const std::string& title ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] CreateWindow" );
	
	engineThread.enqueue( std::make_unique<action::Action>( action::CreateWindowAction( width, height, title ) ) );
}

void CloseWindow() {
	if ( !checkEngine() ) return;

	info(*logger, "[MCGL-ENGINE] CloseWindow");
	engineThread.enqueue(std::make_unique<action::Action>(action::CloseWindowAction()));
}

void Run() {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] Run" );
	engineThread.enqueue( std::make_unique<action::Action>( action::RunAction() ) );
}

void Stop() {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] Stop" );
	engineThread.enqueue(std::make_unique<action::Action>(action::StopAction()));
}

void RegisterBlockType( const world::block::Block& block, const NUM32 id ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RegisterBockType" );
	engineThread.enqueue(std::make_unique<action::Action>(action::RegisterBlockTypeAction(block, id)));
}

void SetTextures( const char* path, const UNUM32 textureSize, const UNUM32 textureCount ) {
	if ( !checkEngine() ) return;

	info(*logger, "[MCGL-ENGINE] SetTextures");
	engineThread.enqueue(std::make_unique<action::Action>(action::SetTexturesAction(path, textureSize, textureCount)));
}

void SetShader( const char* vertexShaderPath, const char* fragmentShaderPath ) {
	if ( !checkEngine() ) return;

	info(*logger, "[MCGL-ENGINE] SetShader");
	engineThread.enqueue(std::make_unique<action::Action>(action::SetShaderData(vertexShaderPath, fragmentShaderPath)));
}

void AddChunk( const UNUM32 x, const UNUM32 z, const world::chunk::Chunk& chunk ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] AddChunk" );
	
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
