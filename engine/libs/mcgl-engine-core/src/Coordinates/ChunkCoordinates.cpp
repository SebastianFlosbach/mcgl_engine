#include "Coordinates/ChunkCoordinates.h"

#include "Coordinates/WorldCoordinates.h"
#include "Coordinates/BlockCoordinates.h"


namespace coordinates {


ChunkCoordinates::ChunkCoordinates( NUM32 x, NUM32 z ) : x_( x ), z_( z ) {}


WorldCoordinates ChunkCoordinates::toWorldCoordinates() const {
	float x = x_ * CHUNK_WIDTH * BLOCK_SIZE;
	float z = z_ * CHUNK_LENGTH * BLOCK_SIZE;

	return { x, 0.0f, z };
}

BlockCoordinates ChunkCoordinates::toBlockCoordinates() const {
	NUM32 x = x_ * CHUNK_WIDTH;
	NUM32 z = z_ * CHUNK_LENGTH;

	return { x, 0, z };
}


}
