#pragma once
#include <string>

#define MCGLExport __declspec(dllexport)

void MCGLExport CreateEngine();
void MCGLExport CreateWindow( unsigned int width, unsigned int height, const std::string& title );
void MCGLExport Run();
void MCGLExport DestroyEngine();

//void MCGLExport RegisterBlockType( world::block::Block block, unsigned int id );
