#pragma once

#include <glm/glm.hpp>

#include "../Block/Block.h"


namespace world {
namespace chunk {


constexpr unsigned int CHUNK_WIDTH = 16;
constexpr unsigned int CHUNK_LENGTH = 16;
constexpr unsigned int CHUNK_HEIGHT = 128;

struct Chunk {
public:
	Chunk() = default;

	Chunk( const glm::vec<3, int>& position ) : position_( position ) {
	}

	Chunk( int x, int y, int z ) : Chunk( glm::vec<3, int>{ x, y, z } ) {
	}

	Chunk( const Chunk& other ) = delete;
	Chunk& operator=( const Chunk& other ) = delete;

	void setBlock( block::Block& block, unsigned int x, unsigned int y, unsigned int z ) {
		blocks_[x][y][z] = block;
	}

	const block::Block* getBlock( int x, int y, int z ) const {
		if (	x < 0 || x > CHUNK_WIDTH 
			||	y < 0 || y > CHUNK_HEIGHT 
			||	z < 0 || z > CHUNK_LENGTH ) {
			return nullptr;
		}

		return &blocks_[x][y][z];
	}

private:
	glm::vec<3, int> position_;

	block::Block blocks_[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH];

};


}
}