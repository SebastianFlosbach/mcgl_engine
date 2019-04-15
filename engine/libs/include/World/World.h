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
		newChunks_.insert( { { x, z }, chunk } );
		isValid_ = false;
	}

	void removeChunk( const int x, const int z ) {
		mesh_.erase( { x, z } );
		isValid_ = false;
	}

	std::unordered_map<chunk::ChunkPosition, Mesh_ptr>& getMesh( const block::BlockLibrary& blockLibrary, const texture::TextureAtlas& textureAtlas ) {
		if( !isValid_ ) {
			chunk::ChunkMeshBuilder meshBuilder( blockLibrary );

			for ( auto& chunk : newChunks_ ) {
				mesh_.insert( { chunk.first, std::make_unique<Mesh>( meshBuilder.createChunkMesh( chunk.second, textureAtlas ) ) } );
			}

			newChunks_.clear();

			isValid_ = true;
		}

		return mesh_;
	}

private:
	std::unordered_map<chunk::ChunkPosition, chunk::Chunk> newChunks_;
	std::unordered_map<chunk::ChunkPosition, Mesh_ptr> mesh_;

	bool isValid_{ false };

	void generateMesh() {

	}

};


}