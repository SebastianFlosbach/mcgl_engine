#pragma once

#include <string>
#include <World/Block/Block.h>
#include <World/Chunk/Chunk.h>

#include "mcgl-engine-export.h"
#include "Definition/mcgl_engine_def.h"

MCGL_ENGINE_EXTERN void CreateEngine();
MCGL_ENGINE_EXTERN void DestroyEngine();
MCGL_ENGINE_EXTERN void CreateWindow( unsigned int width, unsigned int height, const std::string& title );
MCGL_ENGINE_EXTERN void Run();
MCGL_ENGINE_EXTERN void RegisterBlockType( const world::block::Block& block, unsigned int id );
MCGL_ENGINE_EXTERN void SetTextures( const char* path, const unsigned int textureSize, const unsigned int textureCount );
MCGL_ENGINE_EXTERN void SetShader( const char* vertexShaderPath, const char* fragmentShaderPath );
MCGL_ENGINE_EXTERN void AddChunk( const unsigned int x, const unsigned int z, const world::chunk::Chunk& chunk );

MCGL_ENGINE_EXTERN void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void RegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
