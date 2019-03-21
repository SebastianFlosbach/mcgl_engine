#include "mcgl-engine.h"

#include <Engine.h>
#include <World/Block/BlockLibrary.h>

#undef CreateWindow

//world::block::BlockLibrary blockLibrary;
std::unique_ptr<Engine> engine;

void CreateEngine() {
	engine = std::make_unique<Engine>();
	engine->init();
}

void CreateWindow( unsigned int width, unsigned int height, const std::string& title ) {
	engine->createWindow( width, height, title );
}

void Run() {
	engine->run();
}

void DestroyEngine() {
	engine.reset();
}

//void RegisterBlockType( world::block::Block block, unsigned int id ) {
//	blockLibrary.addBlock( block, id );
//}