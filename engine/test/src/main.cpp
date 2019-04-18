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

	RegisterBlockType( { true }, 0 );
	RegisterBlockType( { false, 5, 4, 2, 3, 0, 1 }, 1 );

	world::chunk::Chunk chunk = world::chunk::Chunk();
	for ( int x = 0; x < world::chunk::CHUNK_WIDTH; x++ ) {
		for ( int z = 0; z < world::chunk::CHUNK_LENGTH; z++ ) {
			for ( int y = 0; y < 5; y++ ) {
				chunk.setBlock( 1, x, y, z );
			}
		}
	}

	for( int x = -10; x < 11; x++ ) {
		for( int z = -10; z < 11; z++ ) {
			chunk.setPosition( { x, z } );
			AddChunk( chunk );
		}
	}

	Run();

	futureStop.wait();

	return 0;
}