#pragma once

#include <string>
#include <Chunk/Block/Block.h>
#include <Chunk/Chunk.h>

#include "mcgl-engine-export.h"
#include "Definition/mcgl_engine_def.h"


MCGL_ENGINE_EXTERN void CreateEngine();
MCGL_ENGINE_EXTERN void DestroyEngine();
MCGL_ENGINE_EXTERN void Run();
MCGL_ENGINE_EXTERN void Stop();

MCGL_ENGINE_EXTERN void CreateWindow( NUM32 width, NUM32 height, const std::string& title );
MCGL_ENGINE_EXTERN void CloseWindow();
MCGL_ENGINE_EXTERN void RegisterBlockType( const chunk::block::Block& block );
MCGL_ENGINE_EXTERN void SetTextures( const std::string& path, UNUM32 textureSize, UNUM32 textureCount );
MCGL_ENGINE_EXTERN void SetShader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath );

MCGL_ENGINE_EXTERN void AddChunk( const chunk::Chunk& chunk );
MCGL_ENGINE_EXTERN void RemoveChunk( NUM32 x, NUM32 z );

MCGL_ENGINE_EXTERN void CreateCamera( float x = 0.0, float y = 0.0, float z = 0.0, float pitch = 1.0, float yaw = 0.0, float roll = 0.0 );
MCGL_ENGINE_EXTERN void MoveCamera( float dx, float dy, float dz );
MCGL_ENGINE_EXTERN void RotateCamera( float pitch, float yaw, float roll = 0.0 );

MCGL_ENGINE_EXTERN void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void RegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void RegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );

MCGL_ENGINE_EXTERN float GetDeltaTime();
MCGL_ENGINE_EXTERN coordinates::WorldCoordinates GetCameraPosition();

MCGL_ENGINE_EXTERN std::string MCGLGetVersion();
