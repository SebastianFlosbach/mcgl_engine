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

std::vector<coordinates::ChunkCoordinates> loadedChunks;

void checkLoadedChunks() {
	coordinates::WorldCoordinates position = GetCameraPosition( 1 );

	coordinates::ChunkCoordinates chunkPos = position.toChunkCoordinates();

	if( std::find( loadedChunks.begin(), loadedChunks.end(), chunkPos ) == loadedChunks.end() ) {
		loadedChunks.push_back( chunkPos );
		myChunk.setPosition( chunkPos );
		AddChunk( myChunk );
	}

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
		case MouseEventType::MouseMove:
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

	CreateCamera();

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

	//for ( int x = 0; x < 2; x++ ) {
	//	for ( int z = 0; z < 2; z++ ) {
	//		myChunk.setPosition( { x, z } );
	//		AddChunk( myChunk );
	//	}
	//}

	Run();

	futureStop.wait();

	return 0;
}
