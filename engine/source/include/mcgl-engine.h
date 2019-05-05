#pragma once

#include <string>
#include <Chunk/Block/Block.h>
#include <Chunk/Chunk.h>

#include "mcgl-engine-export.h"
#include "Definition/mcgl_engine_def.h"


MCGL_ENGINE_EXTERN void CreateEngine();
MCGL_ENGINE_EXTERN void DestroyEngine();
MCGL_ENGINE_EXTERN void CreateWindow( NUM32 width, NUM32 height, const std::string& title );
MCGL_ENGINE_EXTERN void CloseWindow();
MCGL_ENGINE_EXTERN void Run();
MCGL_ENGINE_EXTERN void Stop();
MCGL_ENGINE_EXTERN void RegisterBlockType( const chunk::block::Block& block );
MCGL_ENGINE_EXTERN void SetTextures( const std::string& path, UNUM32 textureSize, UNUM32 textureCount );
MCGL_ENGINE_EXTERN void SetShader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath );
MCGL_ENGINE_EXTERN void AddChunk( const chunk::Chunk& chunk );
MCGL_ENGINE_EXTERN void RemoveChunk( NUM32 x, NUM32 z );

MCGL_ENGINE_EXTERN UNUM32 CreateCamera( double x = 0.0, double y = 0.0, double z = 0.0, double pitch = 1.0, double yaw = 0.0, double roll = 0.0 );
MCGL_ENGINE_EXTERN void MoveCamera( UNUM32 cameraId, double dx, double dy, double dz );
MCGL_ENGINE_EXTERN void RotateCamera( UNUM32 cameraId, double pitch, double yaw, double roll = 0.0 );

MCGL_ENGINE_EXTERN void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void RegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback );
MCGL_ENGINE_EXTERN void RegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback );

MCGL_ENGINE_EXTERN float GetDeltaTime();
MCGL_ENGINE_EXTERN coordinates::WorldCoordinates GetCameraPosition( UNUM32 cameraId );
