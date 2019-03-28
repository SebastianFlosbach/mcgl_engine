#include "mcgl-engine.h"

#include <Engine.h>
#include <Logging/SpdFileLogger.h>

#undef CreateWindow

const std::string loggerName { "mcgl_file_logger" };
const std::string loggerPath { "logs/mcgllog.log" };

std::unique_ptr<SpdFileLogger> logger;
std::unique_ptr<Engine> engine;

void CreateEngine() {
	logger = std::make_unique<SpdFileLogger>( loggerName, loggerPath );
	info( *logger, "[MCGL-ENGINE] CreateEngine" );
	engine = std::make_unique<Engine>( *logger.get() );
}

void DestroyEngine() {
	info( *logger, "[MCGL-ENGINE] DestroyEngine" );
	engine.reset();
}

void CreateWindow( unsigned int width, unsigned int height, const std::string& title ) {
	info( *logger, "[MCGL-ENGINE] CreateWindow" );
	engine->createWindow( width, height, title );
}

void Run() {
	info( *logger, "[MCGL-ENGINE] Run" );
	engine->run();
}

void RegisterBlockType( const world::block::Block& block, unsigned int id ) {
	info( *logger, "[MCGL-ENGINE] RegisterBockType" );
	engine->addBlockType( block, id );
}

void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	info( *logger, "[MCGL-ENGINE] RegisterKeyEventCallback" );
	engine->registerKeyEventCallback( callback );
}

void RegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {

}
