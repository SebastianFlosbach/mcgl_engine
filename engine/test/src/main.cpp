#include <iostream>

#include <GLFW/glfw3.h>
#include <mutex>

#include <mcgl-engine.h>
#include <future>

#include "Coordinates/ChunkCoordinates.h"
#include "Coordinates/WorldCoordinates.h"


static double movementSpeed = 15.0;

world::mesh::chunk::Chunk myChunk;

static bool isRunning = true;
static double deltaTime = 1.0;

coordinates::ChunkCoordinates lastChunkPosition{ 0, 0 };

constexpr int RENDER_DISTANCE = 5;

void checkLoadedChunks() {
	coordinates::WorldCoordinates position = MCGLGetCameraPosition();

	coordinates::ChunkCoordinates chunkPos = position.toChunkCoordinates();

	if( chunkPos != lastChunkPosition ) {
		if( chunkPos.x_ - lastChunkPosition.x_ > 0 ) {
			for( int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++ ) {
				myChunk.setPosition( { chunkPos.x_ + RENDER_DISTANCE, chunkPos.z_ + i } );
				MCGLAddChunk( myChunk );
				MCGLRemoveChunk( lastChunkPosition.x_ - RENDER_DISTANCE, lastChunkPosition.z_ + i );
			}
		} else if( chunkPos.x_ - lastChunkPosition.x_ < 0 ) {
			for( int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++ ) {
				myChunk.setPosition( { chunkPos.x_ - RENDER_DISTANCE, chunkPos.z_ + i } );
				MCGLAddChunk( myChunk );
				MCGLRemoveChunk( lastChunkPosition.x_ + RENDER_DISTANCE, lastChunkPosition.z_ + i );
			}
		}

		if( chunkPos.z_ - lastChunkPosition.z_ > 0 ) {
			for( int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++ ) {
				myChunk.setPosition( { chunkPos.x_ + i, chunkPos.z_ + RENDER_DISTANCE } );
				MCGLAddChunk( myChunk );
				MCGLRemoveChunk( lastChunkPosition.x_ + i, lastChunkPosition.z_ -RENDER_DISTANCE );
			}
		} else if( chunkPos.z_ - lastChunkPosition.z_ < 0 ) {
			for( int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++ ) {
				myChunk.setPosition( { chunkPos.x_ + i, chunkPos.z_ - RENDER_DISTANCE } );
				MCGLAddChunk( myChunk );
				MCGLRemoveChunk( lastChunkPosition.x_ + i, lastChunkPosition.z_ + RENDER_DISTANCE );
			}
		}
	}

	lastChunkPosition = chunkPos;

}

void keyEventCallback( const eventing::KeyEvent& keyEvent ) {
	if ( keyEvent.type_ == eventing::KeyEventType::Pressed || keyEvent.type_ == eventing::KeyEventType::Down ) {
		switch ( keyEvent.key_ ) {
			case GLFW_KEY_W:
				MCGLMoveCamera( 0.0, 0.0, movementSpeed * deltaTime );
				checkLoadedChunks();
				break;
			case GLFW_KEY_S:
				MCGLMoveCamera( 0.0, 0.0, -movementSpeed * deltaTime );
				checkLoadedChunks();
				break;
			case GLFW_KEY_A:
				MCGLMoveCamera( -movementSpeed * deltaTime, 0.0, 0.0 );
				checkLoadedChunks();
				break;
			case GLFW_KEY_D:
				MCGLMoveCamera( movementSpeed * deltaTime, 0.0, 0.0 );
				checkLoadedChunks();
				break;
			case GLFW_KEY_ESCAPE:
				MCGLStop();
			default:
				break;
		}
	}
}

static int oldX;
static int oldY;
static bool firstMouse = true;

void mouseEventCallback( const eventing::MouseEvent& mouseEvent ) {
	switch ( mouseEvent.type_ ) {
		case eventing::MouseEventType::ButtonPess:
			break;
		case eventing::MouseEventType::ButtonRelease:
			break;
		case eventing::MouseEventType::Scroll:
			break;
		case eventing::MouseEventType::Move:
		{
			auto newPosition = mouseEvent.data_.position_;
			auto newX = newPosition.x_;
			auto newY = newPosition.y_;

			if ( firstMouse ) {
				oldX = newX;
				oldY = newY;
				firstMouse = false;
			}

			auto dx = newX - oldX;
			auto dy = oldY - newY;

			oldX = newX;
			oldY = newY;

			constexpr float sensitivity = 0.003f;

			dx *= sensitivity;
			dy *= sensitivity;

			MCGLRotateCamera( dy, dx );
		}
			break;
		default:
			break;
	}
}

void statusEventCallback( const eventing::StatusEvent& statusEvent ) {
	if ( statusEvent.type_ == eventing::StatusEventType::Stopped ) {
		isRunning = false;
	}
}

static const float frameTime = 1.0f / 60.0f;

int main() {

	MCGLCreateEngine();
	MCGLCreateWindow( 800, 600, "MCGL" );

	MCGLCreateCamera( 8, 10, 8 );

	MCGLRegisterKeyEventCallback( keyEventCallback );
	MCGLRegisterMouseEventCallback( mouseEventCallback );
	MCGLRegisterStatusEventCallback( statusEventCallback );

	MCGLSetTexture( MCGLTextureType::ATLAS, "BlockTextures", "../resources/textures/mcgl-texture-atlas.png", 16, 4 );
	MCGLSetShader( MCGLShaderType::CUBE, "../resources/shaders/vertexShader", "../resources/shaders/fragmentShader" );

	MCGLSetTexture( MCGLTextureType::SINGLE, "SkyboxRight", "../resources/textures/skybox/right.jpg" );
	MCGLSetTexture( MCGLTextureType::SINGLE, "SkyboxLeft", "../resources/textures/skybox/left.jpg" );
	MCGLSetTexture( MCGLTextureType::SINGLE, "SkyboxTop", "../resources/textures/skybox/top.jpg" );
	MCGLSetTexture( MCGLTextureType::SINGLE, "SkyboxBottom", "../resources/textures/skybox/bottom.jpg" );
	MCGLSetTexture( MCGLTextureType::SINGLE, "SkyboxFront", "../resources/textures/skybox/front.jpg" );
	MCGLSetTexture( MCGLTextureType::SINGLE, "SkyboxBack", "../resources/textures/skybox/back.jpg" );
	MCGLSetShader( MCGLShaderType::SKYBOX, "../resources/shaders/skyboxVertexShader", "../resources/shaders/skyboxFragmentShader" );

	MCGLRegisterBlockType( { 0, true } );
	MCGLRegisterBlockType( { 1, false, 2, 2, 2, 2, 0, 1 } );

	myChunk = world::mesh::chunk::Chunk();
	for ( int x = 0; x < CHUNK_WIDTH; x++ ) {
		for ( int z = 0; z < CHUNK_LENGTH; z++ ) {
			for ( int y = 0; y < 5; y++ ) {
				myChunk.setBlock( x, y, z, 1 );
			}
		}
	}

	for( int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; x++ ) {
		for( int y = -RENDER_DISTANCE; y <= RENDER_DISTANCE; y++ ) {
			myChunk.setPosition( { x, y } );
			MCGLAddChunk( myChunk );
		}
	}

	MCGLRun();

	auto last = std::chrono::steady_clock::now();

	while( isRunning ) {
		auto now = std::chrono::steady_clock::now();
		auto leastDeltaTime = (double)std::chrono::duration_cast<std::chrono::microseconds>(now - last).count() / (double)1000000;
		if( leastDeltaTime < 0.017 ) {
			deltaTime = 0.017;
			std::this_thread::sleep_for( std::chrono::microseconds( (long)(0.017 - deltaTime) * 1000000 ) );
		}
		else {
			deltaTime = leastDeltaTime;
		}
		last = now;
	}

	MCGLDestroyEngine();

	return 0;
}
