#pragma once

#include <glm/glm.hpp>

#include "../Block/Block.h"

struct Chunk {
public:
	Chunk() = default;

	Chunk( const glm::vec<3, int>& position ) : position_( position ) {
	}

	Chunk( int x, int y, int z ) : Chunk( glm::vec<3, int>{ x, y, z } ) {
	}

	Chunk( const Chunk& other ) = delete;
	Chunk& operator=( const Chunk& other ) = delete;

	void setBlock( Block& block, unsigned int x, unsigned int y, unsigned int z ) {
		blocks_[x][y][z] = block;
	}
	
private:
	glm::vec<3, int> position_;

	Block blocks_[16][128][16];

};