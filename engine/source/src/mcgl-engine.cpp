#include "mcgl-engine.h"

#include <Engine.h>
#include <Logging/ConsoleLogger.h>

#undef CreateWindow

std::unique_ptr<ConsoleLogger> logger;
std::unique_ptr<Engine> engine;

void CreateEngine() {
	logger = std::make_unique<ConsoleLogger>();
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
