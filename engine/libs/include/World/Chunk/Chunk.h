#pragma once

#include <glm/glm.hpp>

#include "../Block/Block.h"


namespace world {
namespace chunk {

struct ChunkPosition {
	const int x;
	const int z;
};

constexpr unsigned int CHUNK_WIDTH = 16;
constexpr unsigned int CHUNK_LENGTH = 16;
constexpr unsigned int CHUNK_HEIGHT = 128;

struct Chunk {
public:
	Chunk() = default;

	//Chunk( const Chunk& other ) = delete;
	//Chunk& operator=( const Chunk& other ) = delete;

	void setBlock( unsigned int id, unsigned int x, unsigned int y, unsigned int z ) {
		blocks_[x][y][z] = id;
	}

	int getBlockId( int x, int y, int z ) const {
		if (	x < 0 || x >= CHUNK_WIDTH 
			||	y < 0 || y >= CHUNK_HEIGHT 
			||	z < 0 || z >= CHUNK_LENGTH ) {
			return -1;
		}

		return blocks_[x][y][z];
	}



private:
	unsigned int blocks_[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH]{ 0 };

};


}
}

namespace std {

template<>
struct hash<world::chunk::ChunkPosition> {
	size_t operator()( const world::chunk::ChunkPosition& chunkPosition ) const noexcept {
		int x, z;

		if ( chunkPosition.x >= 0 ) {
			x = chunkPosition.x * 2;
		} else {
			x = -chunkPosition.x * 2 - 1;
		}

		if ( chunkPosition.z >= 0 ) {
			z = chunkPosition.z * 2;
		} else {
			z = -chunkPosition.z * 2 - 1;
		}

		return ((x + z) * (x + z + 1) / 2) * z;
	}
};

template<>
struct equal_to<world::chunk::ChunkPosition> {
	constexpr bool operator()( const world::chunk::ChunkPosition& left, const world::chunk::ChunkPosition& right ) const {	// apply operator== to operands
		return left.x == right.x && left.z == right.z;
	}
};

}