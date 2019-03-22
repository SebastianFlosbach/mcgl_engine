#include "mcgl-engine.h"

#include <Engine.h>
#include <World/Block/BlockLibrary.h>

#undef CreateWindow

world::block::BlockLibrary blockLibrary;
std::unique_ptr<Engine> engine;

void CreateEngine() {
	engine = std::make_unique<Engine>();
	engine->init();
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
	blockLibrary.addBlock( block, id );
}
