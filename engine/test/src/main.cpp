#include <iostream>

#include <mcgl-engine.h>

void keyEventCallback( const KeyEvent& keyEvent ) {
	std::cout << "Type: " << to_string( keyEvent.type_ ) << ", Key: " << keyEvent.key_ << ", Time: " << keyEvent.timePressed_ << std::endl;
}int main() {

	CreateEngine();
	CreateWindow( 800, 600, "MCGL" );
	RegisterKeyEventCallback( keyEventCallback );
	Run();

	return 0;
}