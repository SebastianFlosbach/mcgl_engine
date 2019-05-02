#include <iostream>

#include <GLFW/glfw3.h>
#include <mutex>

#include <mcgl-engine.h>
#include <future>

static double movementSpeed = 15.0;
static std::promise<void> promiseStop;
static std::future<void> futureStop;

void keyEventCallback( const KeyEvent& keyEvent ) {
	if ( keyEvent.type_ == KeyEventType::Pressed || keyEvent.type_ == KeyEventType::Down ) {
		switch ( keyEvent.key_ ) {
			case GLFW_KEY_W:
				MoveCamera( 1, 0.0, 0.0, movementSpeed * GetDeltaTime() );
				break;
			case GLFW_KEY_S:
				MoveCamera( 1, 0.0, 0.0, -movementSpeed * GetDeltaTime() );
				break;
			case GLFW_KEY_A:
				MoveCamera( 1, -movementSpeed * GetDeltaTime(), 0.0, 0.0 );
				break;
			case GLFW_KEY_D:
				MoveCamera( 1, movementSpeed * GetDeltaTime(), 0.0, 0.0 );
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

	chunk::Chunk chunk = chunk::Chunk();
	for ( int x = 0; x < CHUNK_WIDTH; x++ ) {
		for ( int z = 0; z < CHUNK_LENGTH; z++ ) {
			for ( int y = 0; y < 5; y++ ) {
				chunk.setBlock( x, y, z, 1 );
			}
		}
	}

	Run();

	for( int x = -1; x < 1; x++ ) {
		for( int z = -1; z < 1; z++ ) {
			chunk.setPosition( { x, z } );
			AddChunk( chunk );
			std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
		}
	}

	futureStop.wait();

	return 0;
}