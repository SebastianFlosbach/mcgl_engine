#pragma once

#include <string>
#include <World/Mesh/Chunk/Block/Block.h>
#include <World/Mesh/Chunk/Chunk.h>

#include "mcgl-engine-export.h"
#include "Definition/mcgl_engine_def.h"


MCGL_ENGINE_EXTERN void MCGLCreateEngine();
MCGL_ENGINE_EXTERN void MCGLDestroyEngine();
MCGL_ENGINE_EXTERN void MCGLRun();
MCGL_ENGINE_EXTERN void MCGLStop();

MCGL_ENGINE_EXTERN void MCGLCreateWindow( NUM32 width, NUM32 height, const std::string& title );
MCGL_ENGINE_EXTERN void MCGLCloseWindow();
MCGL_ENGINE_EXTERN void MCGLRegisterBlockType( const world::mesh::chunk::block::Block& block );

MCGL_ENGINE_EXTERN void MCGLSetTexture( MCGLTextureType type, const std::string& name, const std::string& path, UNUM32 textureSize = 0, UNUM32 textureCount = 0 );
MCGL_ENGINE_EXTERN void MCGLSetShader( MCGLShaderType type, const std::string& path );

MCGL_ENGINE_EXTERN void MCGLAddChunk( const world::mesh::chunk::Chunk& chunk );
MCGL_ENGINE_EXTERN void MCGLRemoveChunk( NUM32 x, NUM32 z );
MCGL_ENGINE_EXTERN void MCGLUpdateChunk( NUM32 x, NUM32 z, const world::mesh::chunk::block::Block& block );

MCGL_ENGINE_EXTERN void MCGLCreateCamera( float x = 0.0, float y = 0.0, float z = 0.0, float pitch = 1.0, float yaw = 0.0, float roll = 0.0 );
MCGL_ENGINE_EXTERN void MCGLMoveCamera( float dx, float dy, float dz );
MCGL_ENGINE_EXTERN void MCGLRotateCamera( float pitch, float yaw, float roll = 0.0 );

MCGL_ENGINE_EXTERN void MCGLRegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void MCGLRegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void MCGLRegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );

MCGL_ENGINE_EXTERN coordinates::WorldCoordinates MCGLGetCameraPosition();

MCGL_ENGINE_EXTERN void MCGLSet( MCGLSetType type, void* data );
