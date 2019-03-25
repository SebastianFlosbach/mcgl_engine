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
	engine = std::make_unique<Engine>( *logger.get() );
}

void DestroyEngine() {
	engine.reset();
}

void CreateWindow( unsigned int width, unsigned int height, const std::string& title ) {
	engine->createWindow( width, height, title );
}

void Run() {
	engine->run();
}

void RegisterBlockType( const world::block::Block& block, unsigned int id ) {
	engine->addBlockType( block, id );
}

void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	engine->registerKeyEventCallback( callback );
}
