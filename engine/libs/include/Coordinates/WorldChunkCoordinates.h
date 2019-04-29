#pragma once

#include "Definition/mcgl_engine_def.h"


struct WorldCoordinates {

};





ChunkCoordinates toChunkCoordinates( const BlockCoordinates& worldCoords );
BlockCoordinates toWorldCoordinates( const ChunkCoordinates& chunkCoords );


namespace std {

	template<>
	struct hash<ChunkCoordinates> {
		size_t operator()( const ChunkCoordinates& ChunkCoordinates ) const noexcept {
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
	struct equal_to<ChunkCoordinates> {
		constexpr bool operator()( const ChunkCoordinates& left, const ChunkCoordinates& right ) const {	// apply operator== to operands
			return left.x_ == right.x_ && left.z_ == right.z_;
		}
	};

}