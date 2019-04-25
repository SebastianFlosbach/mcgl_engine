#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "Mesh/Mesh.h"
#include "Helper/WorldChunkCoordinates.h"
#include "World/Chunk/ThreadedChunkMeshBuilder.h"
#include "World/Chunk/Chunk.h"


namespace world {

	class World {
	public:
		World( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas );

		World( const World& other ) = delete;
		World& operator=( const World& other ) = delete;

		World( World&& other ) = delete;
		World& operator=( World&& other ) = delete;

		void addChunk( const chunk::Chunk& chunk );

		void removeChunk( const int x, const int z ) {
			worldChunks_.erase( { x, z } );
			removeMesh( { x, z } );
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

		std::mutex mMesh_;

		chunk::ThreadedChunkMeshBuilder_ptr pChunkMeshBuilder_;

		void addMesh( const ChunkCoordinates & position, Mesh_ptr && mesh ) {
			std::lock_guard<std::mutex> lock( mMesh_ );
			mesh_.emplace( position, std::move( mesh ) );
		}

		inline void removeMesh( const ChunkCoordinates & position ) {
			std::lock_guard<std::mutex> lock( mMesh_ );
			mesh_.erase( position );
		}
	};


}