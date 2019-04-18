#pragma once

#include <glm/glm.hpp>

#include "World/Block/Block.h"
#include "Helper/WorldChunkCoordinates.h"


namespace world {
namespace chunk {

struct Chunk {
public:
	Chunk() = default;

	Chunk( const Chunk& other ) {
		*this = other;
	}

	Chunk& operator=( const Chunk& other ) {
		if( this == &other ) {
			return *this;
		}

		memcpy( blocks_, other.blocks_, sizeof( blocks_ ) );
		position_ = other.position_;

		return *this;
	}

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

	void setPosition( const ChunkCoordinates& position ) {
		position_ = position;
	}

	const ChunkCoordinates& getPosition() const {
		return position_;
	}



private:
	unsigned int blocks_[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH]{ 0 };
	ChunkCoordinates position_{ 0, 0 };

};


}
}

namespace std {

template<>
struct hash<ChunkCoordinates> {
	size_t operator()( const ChunkCoordinates& ChunkCoordinates ) const noexcept {
		int x, z;

		if ( ChunkCoordinates.x_ >= 0 ) {
			x = ChunkCoordinates.x_ * 2;
		} else {
			x = -ChunkCoordinates.x_ * 2 - 1;
		}

		if ( ChunkCoordinates.z_ >= 0 ) {
			z = ChunkCoordinates.z_ * 2;
		} else {
			z = -ChunkCoordinates.z_ * 2 - 1;
		}

		return ((x + z) * (x + z + 1) / 2) * z;
	}
};

template<>
struct equal_to<ChunkCoordinates> {
	constexpr bool operator()( const ChunkCoordinates& left, const ChunkCoordinates& right ) const {	// apply operator== to operands
		return left.x_ == right.x_ && left.z_ == right.z_;
	}
};

}