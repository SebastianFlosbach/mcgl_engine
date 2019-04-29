#pragma once

#include <future>
#include <ctpl_stl.h>

#include "Mesh/Mesh.h"
#include "World/Chunk/ChunkMeshBuilder.h"

namespace world {
	namespace chunk {

		/**
			Callback to return created meshes
			\param position Position of the chunk the mesh was build from
			\param mesh Pointer to the generated mesh
		*/
		typedef std::function<void( const ChunkCoordinates& position, Mesh* mesh )> CHUNK_MESH_BUILDER_CALLBACK;

		/**
			Class to create meshes from chunks asynchronously
			\see ChunkMeshBuilder
		*/
		class ThreadedChunkMeshBuilder : private ChunkMeshBuilder {
		public:

			/**
				Create ThreadedChunkMeshBuilder.
				\param blockLibrary BlockLibrary for interpreting chunk data
				\param textureAtlas TextureAtlas to use for the mesh
				\param threadCount Number of threads the builder is allowed to use
			*/
			ThreadedChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas, const unsigned int threadCount );

			/**
				Create the mesh for chunk at a position in the world
				\param position Position of the chunk
				\param world World the chunk is in
				\param callback Callback that returns the generated mesh. \see CHUNK_MESH_BUILDER_CALLBACK
				\return Mesh pointer or nullptr if chunk does not exist
			*/
			void createChunkMesh( const ChunkCoordinates& position, world::World& world, CHUNK_MESH_BUILDER_CALLBACK callback );

		private:
			ctpl::thread_pool threadPool_;

		};

		typedef std::unique_ptr<ThreadedChunkMeshBuilder> ThreadedChunkMeshBuilder_ptr;
	}
}
