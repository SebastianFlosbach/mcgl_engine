#pragma once

#include <vector>

#include "World/Chunk/Chunk.h"
#include "World/Block/BlockLibrary.h"
#include "Mesh/Mesh.h"


namespace world {
	class World;

namespace chunk {


class ChunkMeshBuilder {
public:
	ChunkMeshBuilder( const block::BlockLibrary& blockLibrary ) : blockLibrary_( blockLibrary ) {
	}

	Mesh_ptr createChunkMesh( const int x, const int z, const World& world, const texture::TextureAtlas& textureAtlas );

private:

	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;

	const block::BlockLibrary& blockLibrary_;

	unsigned int indexBase_ = 0;

	inline void addIndices() {
		indices_.push_back( indexBase_ + 0 );
		indices_.push_back( indexBase_ + 1 );
		indices_.push_back( indexBase_ + 3 );
		indices_.push_back( indexBase_ + 1 );
		indices_.push_back( indexBase_ + 2 );
		indices_.push_back( indexBase_ + 3 );
		
		indexBase_ += 4;
	}

};


}
}
