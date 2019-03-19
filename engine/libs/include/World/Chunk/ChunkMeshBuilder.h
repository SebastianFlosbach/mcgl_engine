#pragma once

#include "Chunk.h"
#include "../../Mesh/Mesh.h"

namespace world {
namespace chunk {

class ChunkMeshBuilder {
public:
	static Mesh createChunkMesh( const Chunk& chunk ) {
		for ( int x = 0; x < CHUNK_WIDTH; x++ ) {
			for ( int y = 0; y < CHUNK_HEIGHT; y++ ) {
				for ( int z = 0; z < CHUNK_LENGTH; z++ ) {
					const block::Block* block = chunk.getBlock( x, y, z );

					if ( block == nullptr || block->isTransparent_ ) {
						continue;
					}

					const block::Block* neighbour;

					neighbour = chunk.getBlock( x - 1, y, z );
					if ( neighbour != nullptr && !neighbour->isTransparent_ ) {
						addFace();
					}

					neighbour = chunk.getBlock( x + 1, y, z );
					neighbour = chunk.getBlock( x, y - 1, z );
					neighbour = chunk.getBlock( x, y + 1, z );
					neighbour = chunk.getBlock( x, y, z - 1 );
					neighbour = chunk.getBlock( x, y, z + 1 );
				}
			}
		}
	}

private:
	ChunkMeshBuilder() = default;

	

	static void addFace() {

	}
};

}
}
