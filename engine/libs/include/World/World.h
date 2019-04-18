#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "World/Chunk/ChunkMeshBuilder.h"
#include "Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "Mesh/Mesh.h"
#include "Helper/WorldChunkCoordinates.h"


namespace world {

class World {
public:
	World( const block::BlockLibrary& blockLibrary, const texture::TextureAtlas& textureAtlas ) : pChunkMeshBuilder_( new chunk::ChunkMeshBuilder( blockLibrary, textureAtlas ) ) {}

	World( const World& other ) = delete;
	World& operator=( const World& other ) = delete;

	World( World&& other ) = delete;
	World& operator=( World&& other ) = delete;

	void addChunk( const chunk::Chunk& chunk ) {
		worldChunks_.insert( { { chunk.getPosition().x_, chunk.getPosition().z_ }, chunk } );

		auto& position = chunk.getPosition();

		auto x = position.x_;
		auto z = position.z_;

		if( worldChunks_.find( { x + 1, z } ) != worldChunks_.end() ) {
			mesh_.erase( { x + 1, z } );
			mesh_.insert( { ChunkCoordinates( x + 1, z ), pChunkMeshBuilder_->createChunkMesh( x + 1, z, *this ) } );
		}

		if( worldChunks_.find( { x - 1, z } ) != worldChunks_.end() ) {
			mesh_.erase( { x - 1, z } );
			mesh_.insert( { ChunkCoordinates( x - 1, z ), pChunkMeshBuilder_->createChunkMesh( x - 1, z, *this ) } );
		}
		
		if( worldChunks_.find( { x, z + 1 } ) != worldChunks_.end() ) {
			mesh_.erase( { x, z + 1 } );
			mesh_.insert( { ChunkCoordinates( x, z + 1 ), pChunkMeshBuilder_->createChunkMesh( x, z + 1, *this ) } );
		}		
		
		if( worldChunks_.find( { x, z - 1 } ) != worldChunks_.end() ) {
			mesh_.erase( { x, z - 1 } );
			mesh_.insert( { ChunkCoordinates( x, z - 1 ), pChunkMeshBuilder_->createChunkMesh( x, z - 1, *this ) } );
		}

		mesh_.insert( { position, pChunkMeshBuilder_->createChunkMesh( x, z, *this ) } );
	}

	void removeChunk( const int x, const int z ) {
		worldChunks_.erase( { x, z } );
		mesh_.erase( { x, z } );
	}

	const chunk::Chunk* getChunk( const int x, const int z ) const {
		if( worldChunks_.find( { x, z } ) != worldChunks_.end() ) {
			return &worldChunks_.at( { x, z } );
		}

		return nullptr;
	}

	std::unordered_map<ChunkCoordinates, Mesh_ptr>& getMesh() {
		return mesh_;
	}

private:
	std::unordered_map<ChunkCoordinates, chunk::Chunk> worldChunks_;
	std::unordered_map<ChunkCoordinates, Mesh_ptr> mesh_;

	std::unique_ptr<chunk::ChunkMeshBuilder> pChunkMeshBuilder_;

};


}