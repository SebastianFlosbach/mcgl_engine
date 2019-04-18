#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "World/Chunk/ChunkMeshBuilder.h"
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
		if( worldChunks_.find( { x, z } ) != worldChunks_.end() ) {
			worldChunks_.erase( { x, z } );
			mesh_.erase( { x, z } );
		} else if( newChunks_.find( { x, z } ) != newChunks_.end() ) {
			newChunks_.erase( { x, z } );
		}
		isValid_ = false;
	}

	const chunk::Chunk* getChunk( const int x, const int z ) const {
		if( worldChunks_.find( { x, z } ) != worldChunks_.end() ) {
			return &worldChunks_.at( { x, z } );
		}

		if( newChunks_.find( { x, z } ) != newChunks_.end() ) {
			return &newChunks_.at( { x, z } );
		}

		return nullptr;
	}

	std::unordered_map<chunk::ChunkPosition, Mesh_ptr>& getMesh( const block::BlockLibrary& blockLibrary, const texture::TextureAtlas& textureAtlas ) {
		if( !isValid_ ) {
			chunk::ChunkMeshBuilder meshBuilder( blockLibrary );

			for ( auto& chunk : newChunks_ ) {
				mesh_.insert( { chunk.first, meshBuilder.createChunkMesh( chunk.first.x_, chunk.first.z_, *this, textureAtlas ) } );
			}

			worldChunks_.insert( newChunks_.begin(), newChunks_.end() );
			newChunks_.clear();

			isValid_ = true;
		}

		return mesh_;
	}

private:
	std::unordered_map<chunk::ChunkPosition, chunk::Chunk> newChunks_;
	std::unordered_map<chunk::ChunkPosition, chunk::Chunk> worldChunks_;
	std::unordered_map<chunk::ChunkPosition, Mesh_ptr> mesh_;

	bool isValid_{ false };

};


}