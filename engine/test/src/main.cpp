#include <iostream>

#include <mcgl-engine.h>

void keyEventCallback( const KeyEvent& keyEvent ) {
	std::cout << "Type: " << to_string( keyEvent.type_ ) << ", Key: " << keyEvent.key_ << ", Time: " << keyEvent.timePressed_ << std::endl;
}

void mouseEventCallback( const MouseEvent& mouseEvent ) {

}

int main() {

	CreateEngine();
	CreateWindow( 800, 600, "MCGL" );
	RegisterKeyEventCallback( keyEventCallback );
	RegisterMouseEventCallback( mouseEventCallback );

	SetTextures( "../resources/textures/mcgl_texture_atlas.png", 16, 4 );
	SetShader( "../resources/shaders/vertexShader", "../resources/shaders/fragmentShader" );



	Run();

	return 0;
}