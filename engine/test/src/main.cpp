#include <iostream>

#include <mcgl-engine.h>

#include "Camera.h"

static Camera camera;

void keyEventCallback( const KeyEvent& keyEvent ) {
	std::cout << "Type: " << to_string( keyEvent.type_ ) << ", Key: " << keyEvent.key_ << ", Time: " << keyEvent.timePressed_ << std::endl;
}

static int oldX;
static int oldY;

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

			auto dx = newX - oldX;
			auto dy = oldY - newY;

			oldX = newX;
			oldY = newY;

			float sensitivity = 0.05f;

			dx *= sensitivity;
			dy *= sensitivity;

			camera.rotate( dx, dy );
		}
			break;
		default:
			break;
	}
}

int main() {
	camera = Camera();


	CreateEngine();
	CreateWindow( 800, 600, "MCGL" );

	RegisterKeyEventCallback( keyEventCallback );
	RegisterMouseEventCallback( mouseEventCallback );

	SetTextures( "../resources/textures/mcgl-texture-atlas.png", 16, 4 );
	SetShader( "../resources/shaders/vertexShader", "../resources/shaders/fragmentShader" );

	RegisterBlockType( { true }, 0 );
	RegisterBlockType( { false, 2, 2, 2, 2, 0, 1 }, 1 );

	world::chunk::Chunk chunk = world::chunk::Chunk();
	for ( int x = 0; x < world::chunk::CHUNK_WIDTH; x++ ) {
		for ( int z = 0; z < world::chunk::CHUNK_LENGTH; z++ ) {
			for ( int y = 0; y < 5; y++ ) {
				chunk.setBlock( 1, x, y, z );
			}
		}
	}
	AddChunk( 0, 0, chunk );

	Run();

	return 0;
}