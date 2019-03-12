#include "mcgl-engine.h"

#include "Engine.h"

#undef CreateWindow

std::unique_ptr<Engine> engine;

void CreateEngine() {
	engine = std::make_unique<Engine>();
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