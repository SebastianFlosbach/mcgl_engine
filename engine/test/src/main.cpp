#include <iostream>

#include <GLFW/glfw3.h>
#include <mutex>

#include <mcgl-engine.h>
#include <future>

#include "Coordinates/ChunkCoordinates.h"
#include "Coordinates/WorldCoordinates.h"

static double movementSpeed = 15.0;
static std::promise<void> promiseStop;
static std::future<void> futureStop;

chunk::Chunk myChunk;

coordinates::ChunkCoordinates lastChunkPosition{ 0, 0 };

constexpr int RENDER_DISTANCE = 5;

void checkLoadedChunks() {
	coordinates::WorldCoordinates position = GetCameraPosition();

	coordinates::ChunkCoordinates chunkPos = position.toChunkCoordinates();

	if( chunkPos != lastChunkPosition ) {
		if( chunkPos.x_ - lastChunkPosition.x_ > 0 ) {
			for( int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++ ) {
				myChunk.setPosition( { chunkPos.x_ + RENDER_DISTANCE, chunkPos.z_ + i } );
				AddChunk( myChunk );
				RemoveChunk( lastChunkPosition.x_ - RENDER_DISTANCE, lastChunkPosition.z_ + i );
			}
		} else if( chunkPos.x_ - lastChunkPosition.x_ < 0 ) {
			for( int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++ ) {
				myChunk.setPosition( { chunkPos.x_ - RENDER_DISTANCE, chunkPos.z_ + i } );
				AddChunk( myChunk );
				RemoveChunk( lastChunkPosition.x_ + RENDER_DISTANCE, lastChunkPosition.z_ + i );
			}
		}

		if( chunkPos.z_ - lastChunkPosition.z_ > 0 ) {
			for( int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++ ) {
				myChunk.setPosition( { chunkPos.x_ + i, chunkPos.z_ + RENDER_DISTANCE } );
				AddChunk( myChunk );
				RemoveChunk( lastChunkPosition.x_ + i, lastChunkPosition.z_ -RENDER_DISTANCE );
			}
		} else if( chunkPos.z_ - lastChunkPosition.z_ < 0 ) {
			for( int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++ ) {
				myChunk.setPosition( { chunkPos.x_ + i, chunkPos.z_ - RENDER_DISTANCE } );
				AddChunk( myChunk );
				RemoveChunk( lastChunkPosition.x_ + i, lastChunkPosition.z_ + RENDER_DISTANCE );
			}
		}
	}

	lastChunkPosition = chunkPos;

}

void keyEventCallback( const KeyEvent& keyEvent ) {
	if ( keyEvent.type_ == KeyEventType::Pressed || keyEvent.type_ == KeyEventType::Down ) {
		switch ( keyEvent.key_ ) {
			case GLFW_KEY_W:
				MoveCamera( 1, 0.0, 0.0, movementSpeed * GetDeltaTime() );
				checkLoadedChunks();
				break;
			case GLFW_KEY_S:
				MoveCamera( 1, 0.0, 0.0, -movementSpeed * GetDeltaTime() );
				checkLoadedChunks();
				break;
			case GLFW_KEY_A:
				MoveCamera( 1, -movementSpeed * GetDeltaTime(), 0.0, 0.0 );
				checkLoadedChunks();
				break;
			case GLFW_KEY_D:
				MoveCamera( 1, movementSpeed * GetDeltaTime(), 0.0, 0.0 );
				checkLoadedChunks();
				break;
			case GLFW_KEY_ESCAPE:
				Stop();
			default:
				break;
		}
	}
}

static int oldX;
static int oldY;
static bool firstMouse = true;

void mouseEventCallback( const MouseEvent& mouseEvent ) {
	switch ( mouseEvent.type_ ) {
		case MouseEventType::ButtonPess:
			break;
		case MouseEventType::ButtonRelease:
			break;
		case MouseEventType::Scroll:
			break;
		case MouseEventType::Move:
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

			float sensitivity = 0.003f;

			dx *= sensitivity;
			dy *= sensitivity;

			RotateCamera( 1, dy, dx );
		}
			break;
		default:
			break;
	}
}

void statusEventCallback( const StatusEvent& statusEvent ) {
	if ( statusEvent.type_ == StatusEventType::Stopped ) {
		promiseStop.set_value();
	}
}

static const float frameTime = 1.0f / 60.0f;

int main() {
	promiseStop = std::promise<void>();
	futureStop = promiseStop.get_future();

	CreateEngine();
	CreateWindow( 800, 600, "MCGL" );

	CreateCamera( 8, 10, 8 );

	RegisterKeyEventCallback( keyEventCallback );
	RegisterMouseEventCallback( mouseEventCallback );
	RegisterStatusEventCallback( statusEventCallback );

	SetTextures( "../resources/textures/mcgl-texture-atlas.png", 16, 4 );
	SetShader( "../resources/shaders/vertexShader", "../resources/shaders/fragmentShader" );

	RegisterBlockType( { 0, true } );
	RegisterBlockType( { 1, false, 2, 2, 2, 2, 0, 1 } );

	myChunk = chunk::Chunk();
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
			AddChunk( myChunk );
		}
	}

	Run();

	futureStop.wait();

	DestroyEngine();

	return 0;
}
