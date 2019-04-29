#include "World/Chunk/Builder/ThreadedChunkMeshBuilder.h"

#include "World/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "World/World.h"
#include "World/Chunk/Builder/ChunkMeshBuilder.h"

namespace world {
	namespace chunk {

		ThreadedChunkMeshBuilder::ThreadedChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas, const unsigned int threadCount ) :
			ChunkMeshBuilder( blockLibrary, textureAtlas ),
			threadPool_( threadCount ) 
		{}

		void ThreadedChunkMeshBuilder::build( const ChunkCoordinates& position, const ChunkCollection& chunks, CHUNK_MESH_BUILDER_CALLBACK& callback ) {
			threadPool_.push( [this, &position, &chunks, &callback]( int id ) {
				auto* mesh = ChunkMeshBuilder::createChunkMesh( position, world );
				callback( position, mesh );
			} );
		}

	}
}