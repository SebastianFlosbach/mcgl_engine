#pragma once

#include <string>
#include <World/Block/Block.h>
#include <World/Chunk/Chunk.h>

#include "mcgl-engine-export.h"
#include "Definition/mcgl_engine_def.h"


MCGL_ENGINE_EXTERN void CreateEngine();
MCGL_ENGINE_EXTERN void DestroyEngine();
MCGL_ENGINE_EXTERN void CreateWindow( const NUM32 width, const NUM32 height, const std::string& title );
MCGL_ENGINE_EXTERN void CloseWindow();
MCGL_ENGINE_EXTERN void Run();
MCGL_ENGINE_EXTERN void Stop();
MCGL_ENGINE_EXTERN void RegisterBlockType( const world::block::Block& block, NUM32 id );
MCGL_ENGINE_EXTERN void SetTextures( const char* path, const UNUM32 textureSize, const UNUM32 textureCount );
MCGL_ENGINE_EXTERN void SetShader( const char* vertexShaderPath, const char* fragmentShaderPath );
MCGL_ENGINE_EXTERN void AddChunk( const world::chunk::Chunk& chunk );

MCGL_ENGINE_EXTERN UNUM32 CreateCamera( const double x = 0.0, const double y = 0.0, const double z = 0.0, const double pitch = 1.0, const double yaw = 0.0, const double roll = 0.0 );
MCGL_ENGINE_EXTERN void MoveCamera( const UNUM32 cameraId, const double dx, const double dy, const double dz );
MCGL_ENGINE_EXTERN void RotateCamera( const UNUM32 cameraId, const double pitch, const double yaw, const double roll = 0.0 );

MCGL_ENGINE_EXTERN void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void RegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void RegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );

MCGL_ENGINE_EXTERN float GetDeltaTime();
