#include "Coordinates/WorldCoordinates.h"

#include "Coordinates/ChunkCoordinates.h"


namespace coordinates {


WorldCoordinates::WorldCoordinates( float x, float y, float z ) : x_( x ), y_( y ), z_( z ) {}

WorldCoordinates::WorldCoordinates( const glm::vec3 position ) : WorldCoordinates( position.x, position.y, position.z ) {}


glm::vec3 WorldCoordinates::toVec3() const {
	return { x_, y_, z_ };
}

ChunkCoordinates WorldCoordinates::toChunkCoordinates() const {
	NUM32 x = floor( x_ / (float)CHUNK_WIDTH );
	NUM32 z = floor( z_ / (float)CHUNK_LENGTH );

	return { x, z };
}


}