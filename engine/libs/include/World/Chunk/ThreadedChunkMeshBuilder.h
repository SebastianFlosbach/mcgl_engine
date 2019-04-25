#pragma once

#include <future>
#include <ctpl_stl.h>

#include "Mesh/Mesh.h"

struct ChunkCoordinates;

namespace world {

	class World;

	namespace block {
		struct Block;
		class BlockLibrary;
	}

	namespace chunk {

		class ChunkMeshBuilder;

		typedef std::function<void( const ChunkCoordinates& position, Mesh_ptr&& mesh )> CHUNK_MESH_BUILDER_CALLBACK;

		class ThreadedChunkMeshBuilder {
		public:
			ThreadedChunkMeshBuilder( const block::BlockLibrary& blockLibrary, const texture::TextureAtlas& textureAtlas, const unsigned int threadCount );

			void createChunkMesh( int x, int z, world::World& world, CHUNK_MESH_BUILDER_CALLBACK callback );

		private:
			ctpl::thread_pool threadPool_;
			std::unique_ptr<ChunkMeshBuilder> pChunkMeshBuilder_;

		};

		typedef std::unique_ptr<ThreadedChunkMeshBuilder> ThreadedChunkMeshBuilder_ptr;
	}
}
