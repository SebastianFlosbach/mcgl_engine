#include "Coordinates/BlockCoordinates.h"

#include "Coordinates/ChunkCoordinates.h"
#include "Coordinates/WorldCoordinates.h"


namespace coordinates {


BlockCoordinates::BlockCoordinates( NUM32 x, NUM32 y, NUM32 z ) : x_( x ), y_( y ), z_( z ) {}

ChunkCoordinates BlockCoordinates::toChunkCoordinates() const {
	NUM32 x = floor((float)x_ / (float)CHUNK_WIDTH);
	NUM32 z = floor((float)z_ / (float)CHUNK_LENGTH);

	return { x, z };
}

WorldCoordinates BlockCoordinates::toWorldCoordinates() const {
	float x = x_ * BLOCK_SIZE;
	float y = y_ * BLOCK_SIZE;
	float z = z_ * BLOCK_SIZE;

	return { x, y, z };
}


}
