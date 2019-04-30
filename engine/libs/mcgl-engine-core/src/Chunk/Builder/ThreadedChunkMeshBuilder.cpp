#include "Chunk/Builder/ThreadedChunkMeshBuilder.h"

#include "Chunk/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "World/World.h"
#include "Chunk/Builder/ChunkMeshBuilder.h"


namespace chunk {
namespace builder{


ThreadedChunkMeshBuilder::ThreadedChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas, const unsigned int threadCount ) :
	ChunkMeshBuilder( blockLibrary, textureAtlas ),
	threadPool_( threadCount ) {
}

void ThreadedChunkMeshBuilder::build( const ChunkCoordinates& position, const ChunkCollection& chunks ) {
	threadPool_.push( [this, &position, &chunks]( int id ) {
		auto* mesh = ChunkMeshBuilder::build( position, chunks );

		if ( callback_ ) {
			callback_( position, mesh );
		}
	} );
}

void ThreadedChunkMeshBuilder::registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) {
	callback_ = callback;
}

void ThreadedChunkMeshBuilder::deregisterCallback() {
	callback_ = NULL;
}


}
}
