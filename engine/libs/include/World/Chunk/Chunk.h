#pragma once

#include <glm/glm.hpp>

#include "../Block/Block.h"


namespace world {
namespace chunk {

struct ChunkPosition {
	ChunkPosition( int x, int z ) : x_( x ), z_( z ) {}

	ChunkPosition( const ChunkPosition& other ) {
		*this = other;
	}

	ChunkPosition& operator=( const ChunkPosition& other ) {
		if( this == &other ) {
			return *this;
		}

		x_ = other.x_;
		z_ = other.z_;

		return *this;
	}

	int x_;
	int z_;
};

constexpr unsigned int CHUNK_WIDTH = 16;
constexpr unsigned int CHUNK_LENGTH = 16;
constexpr unsigned int CHUNK_HEIGHT = 128;

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

	void setPosition( const ChunkPosition& position ) {
		position_ = position;
	}

	const ChunkPosition& getPosition() const {
		return position_;
	}



private:
	unsigned int blocks_[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH]{ 0 };
	ChunkPosition position_{ 0, 0 };

};


}
}

namespace std {

template<>
struct hash<world::chunk::ChunkPosition> {
	size_t operator()( const world::chunk::ChunkPosition& chunkPosition ) const noexcept {
		int x, z;

		if ( chunkPosition.x_ >= 0 ) {
			x = chunkPosition.x_ * 2;
		} else {
			x = -chunkPosition.x_ * 2 - 1;
		}

		if ( chunkPosition.z_ >= 0 ) {
			z = chunkPosition.z_ * 2;
		} else {
			z = -chunkPosition.z_ * 2 - 1;
		}

		return ((x + z) * (x + z + 1) / 2) * z;
	}
};

template<>
struct equal_to<world::chunk::ChunkPosition> {
	constexpr bool operator()( const world::chunk::ChunkPosition& left, const world::chunk::ChunkPosition& right ) const {	// apply operator== to operands
		return left.x_ == right.x_ && left.z_ == right.z_;
	}
};

}