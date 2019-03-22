#pragma once

#include <string>
#include <World/Block/Block.h>

#include "mcgl-engine-export.h"

MCGL_ENGINE_EXTERN void CreateEngine();
MCGL_ENGINE_EXTERN void CreateWindow( unsigned int width, unsigned int height, const std::string& title );
MCGL_ENGINE_EXTERN void Run();
MCGL_ENGINE_EXTERN void RegisterBlockType( const world::block::Block& block, unsigned int id );
MCGL_ENGINE_EXTERN void DestroyEngine();

//void MCGLExport RegisterBlockType( world::block::Block block, unsigned int id );
