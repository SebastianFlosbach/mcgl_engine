#pragma once

#include "Definition/mcgl_engine_def.h"
#include "Coordinates/BlockCoordinates.h"
#include "Coordinates/WorldCoordinates.h"


namespace coordinates {


struct ChunkCoordinates {
	ChunkCoordinates( NUM32 x, NUM32 z ) : x_( x ), z_( z ) {}


	WorldCoordinates toWorldCoordinates() const {
		float x = x_ * CHUNK_WIDTH * BLOCK_SIZE;
		float z = z_ * CHUNK_LENGTH * BLOCK_SIZE;

		return { x, 0.0f, z };
	}

	BlockCoordinates toBlockCoordinates() const {
		NUM32 x = x_ * CHUNK_WIDTH;
		NUM32 z = z_ * CHUNK_LENGTH;

		return { x, 0, z };
	}

	NUM32 x_, z_;
};


}

namespace std {

template<>
struct hash<coordinates::ChunkCoordinates> {
	size_t operator()( const coordinates::ChunkCoordinates& ChunkCoordinates ) const noexcept {
		int x, z;

		if( ChunkCoordinates.x_ >= 0 ) {
			x = ChunkCoordinates.x_ * 2;
		}
		else {
			x = -ChunkCoordinates.x_ * 2 - 1;
		}

		if( ChunkCoordinates.z_ >= 0 ) {
			z = ChunkCoordinates.z_ * 2;
		}
		else {
			z = -ChunkCoordinates.z_ * 2 - 1;
		}

		return ((x + z) * (x + z + 1) / 2) * z;
	}
};

template<>
struct equal_to<coordinates::ChunkCoordinates> {
	constexpr bool operator()( const coordinates::ChunkCoordinates& left, const coordinates::ChunkCoordinates& right ) const {	// apply operator== to operands
		return left.x_ == right.x_ && left.z_ == right.z_;
	}
};

}