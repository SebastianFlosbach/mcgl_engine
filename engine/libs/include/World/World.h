#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "Chunk/Chunk.h"
#include "Chunk/ChunkMeshBuilder.h"
#include "Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "Mesh/Mesh.h"
#include "Shader.h"

namespace world {


class World {
public:
	World() = default;

	World( const World& other ) = delete;
	World& operator=( const World& other ) = delete;

	World( World&& other ) = delete;
	World& operator=( World&& other ) = delete;

	void addChunk( unsigned int x, unsigned int z, const chunk::Chunk& chunk ) {
		chunks_.insert( { x, z }, chunk );
	}

	void removeChunk( unsigned int x, unsigned int z ) {
		chunks_.erase( { x, z } );
	}

	std::vector<Mesh> generateMesh( const block::BlockLibrary& blockLibrary, const texture::TextureAtlas& textureAtlas ) {
		chunk::ChunkMeshBuilder meshBuilder( blockLibrary );
		std::vector<Mesh> mesh( chunks_.size() );

		int i = 0;
		for ( auto& chunk : chunks_ ) {
			mesh[i++] = meshBuilder.createChunkMesh( chunk.second, textureAtlas );
		}

		return mesh;
	}

private:
	std::map<glm::vec<2, int>, chunk::Chunk> chunks_;

};


}