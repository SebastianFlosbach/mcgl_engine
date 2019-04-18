#include "Helper/WorldChunkCoordinates.h"

ChunkCoordinates toChunkCoordinates( const WorldCoordinates& worldCoords ) {
	int chunkX = worldCoords.x_ / (int)CHUNK_WIDTH;
	int chunkZ = worldCoords.z_ / (int)CHUNK_LENGTH;

	return { chunkX, chunkZ };
}

WorldCoordinates toWorldCoordinates( const ChunkCoordinates& chunkCoords ) {
	int worldX = chunkCoords.x_ * (int)CHUNK_WIDTH;
	int worldZ = chunkCoords.z_ * (int)CHUNK_LENGTH;

	return { worldX, 0, worldZ };
}