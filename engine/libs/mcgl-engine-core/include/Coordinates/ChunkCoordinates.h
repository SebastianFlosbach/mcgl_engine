#pragma once

#include <functional>
#include <string>

#include "Definition/mcgl_engine_def.h"


namespace coordinates {
struct WorldCoordinates;
struct BlockCoordinates;


struct ChunkCoordinates {
	ChunkCoordinates( NUM32 x, NUM32 z );


	WorldCoordinates toWorldCoordinates() const;

	BlockCoordinates toBlockCoordinates() const;

	NUM32 x_, z_;

	bool operator==( const ChunkCoordinates& right ) const {
		if( x_ == right.x_ && z_ == right.z_ ) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator!=( const ChunkCoordinates& right ) const {
		return !(*this == right);
	}

	std::string to_string() const {
		return std::string( "( " ) + std::to_string( x_ ) + std::string( ", " ) + std::to_string( z_ ) + std::string( " )" );
	}

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