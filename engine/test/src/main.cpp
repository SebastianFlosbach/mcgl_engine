#include <iostream>

#include <mcgl-engine.h>

int main() {

	CreateEngine();
	CreateWindow( 800, 600, "MCGL" );

	world::block::Block air{ true, 0, 0, 0, 0, 0, 0 };
	world::block::Block grass{ false, 2, 2, 2, 2, 0, 1 };
	world::block::Block dirt{ false, 1, 1, 1, 1, 1, 1 };
	world::block::Block stone{ false, 3, 3, 3, 3, 3, 3 };

	RegisterBlockType( air, 0 );
	RegisterBlockType( grass, 1 );
	RegisterBlockType( dirt, 2 );
	RegisterBlockType( stone, 3 );

	Run();

	return 0;
}