#pragma once

#include <cmath>

#include "Definition/mcgl_engine_def.h"


namespace coordinates {


struct BlockCoordinates {
	BlockCoordinates( NUM32 x, NUM32 y, NUM32 z ) : x_( x ), y_( y ), z_( z ) {}

	ChunkCoordinates toChunkCoordinates() const {
		NUM32 x = round( (float)x_ / CHUNK_WIDTH );
		NUM32 z = round( (float)z_ / CHUNK_LENGTH );

		return { x, z };
	}

	WorldCoordinates toWorldCoordinates() const {
		float x = x_ * BLOCK_SIZE;
		float y = y_ * BLOCK_SIZE;
		float z = z_ * BLOCK_SIZE;

		return { x, y, z };
	}

	NUM32 x_, y_, z_;
};


}