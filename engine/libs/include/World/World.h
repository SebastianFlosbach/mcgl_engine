#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
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

	void addChunk( const int x, const int z, const chunk::Chunk& chunk ) {
		chunks_.insert( { { x, z }, chunk } );
		isValid_ = false;
	}

	void removeChunk( const int x, const int z ) {
		chunks_.erase( { x, z } );
		isValid_ = false;
	}

	std::vector<Mesh_ptr>& getMesh( const block::BlockLibrary& blockLibrary, const texture::TextureAtlas& textureAtlas ) {
		if( isValid_ ) {
			return meshCache_;
		}

		chunk::ChunkMeshBuilder meshBuilder( blockLibrary );
		std::vector<std::unique_ptr<Mesh>> mesh( chunks_.size() );

		int i = 0;
		for ( auto& chunk : chunks_ ) {
			mesh[i++] = std::make_unique<Mesh>( meshBuilder.createChunkMesh( chunk.second, textureAtlas ) );
		}

		meshCache_ = std::move( mesh );
		isValid_ = true;

		return meshCache_;
	}

private:
	std::unordered_map<chunk::ChunkPosition, chunk::Chunk> chunks_;
	std::vector<Mesh_ptr> meshCache_;

	bool isValid_{ false };

};


}