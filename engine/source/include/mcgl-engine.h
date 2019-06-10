#pragma once

#include <string>
#include <Chunk/Block/Block.h>
#include <Chunk/Chunk.h>

#include "mcgl-engine-export.h"
#include "Definition/mcgl_engine_def.h"


MCGL_ENGINE_EXTERN void MCGLCreateEngine();
MCGL_ENGINE_EXTERN void MCGLDestroyEngine();
MCGL_ENGINE_EXTERN void MCGLRun();
MCGL_ENGINE_EXTERN void MCGLStop();

MCGL_ENGINE_EXTERN void MCGLCreateWindow( NUM32 width, NUM32 height, const std::string& title );
MCGL_ENGINE_EXTERN void MCGLCloseWindow();
MCGL_ENGINE_EXTERN void MCGLRegisterBlockType( const chunk::block::Block& block );
MCGL_ENGINE_EXTERN void MCGLSetTextures( const std::string& path, UNUM32 textureSize, UNUM32 textureCount );
MCGL_ENGINE_EXTERN void MCGLSetSkyboxTextures( 
	const std::string& right,
	const std::string& left,
	const std::string& top,
	const std::string& bottom,
	const std::string& front,
	const std::string& back 
);
MCGL_ENGINE_EXTERN void MCGLSetShader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath );
MCGL_ENGINE_EXTERN void MCGLSetSkyboxShader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath );

MCGL_ENGINE_EXTERN void MCGLAddChunk( const chunk::Chunk& chunk );
MCGL_ENGINE_EXTERN void MCGLRemoveChunk( NUM32 x, NUM32 z );

MCGL_ENGINE_EXTERN void MCGLCreateCamera( float x = 0.0, float y = 0.0, float z = 0.0, float pitch = 1.0, float yaw = 0.0, float roll = 0.0 );
MCGL_ENGINE_EXTERN void MCGLMoveCamera( float dx, float dy, float dz );
MCGL_ENGINE_EXTERN void MCGLRotateCamera( float pitch, float yaw, float roll = 0.0 );

MCGL_ENGINE_EXTERN void MCGLRegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void MCGLRegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void MCGLRegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );

MCGL_ENGINE_EXTERN coordinates::WorldCoordinates MCGLGetCameraPosition();
