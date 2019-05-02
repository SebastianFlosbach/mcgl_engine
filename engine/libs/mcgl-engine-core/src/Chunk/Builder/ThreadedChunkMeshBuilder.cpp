#include "Chunk/Builder/ThreadedChunkMeshBuilder.h"

#include "Chunk/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "World/World.h"
#include "Chunk/Builder/ChunkMeshBuilder.h"


namespace chunk {
namespace builder{


ThreadedChunkMeshBuilder::ThreadedChunkMeshBuilder( UNUM32 threadCount ) : threadPool_( threadCount ) {
}

ThreadedChunkMeshBuilder::ThreadedChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas, UNUM32 threadCount ) :
	ChunkMeshBuilder( blockLibrary, textureAtlas ),
	threadPool_( threadCount ) {
}

void ThreadedChunkMeshBuilder::build( const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks ) {
	threadPool_.push( [this, position, &chunks]( int id ) {
		auto* mesh = ChunkMeshBuilder::build( position, chunks );

		if ( callback_ ) {
			callback_( position, mesh );
		}
	} );
}

void ThreadedChunkMeshBuilder::setBlockLibrary( const block::BlockLibrary_sptr& blockLibrary ) {
	ChunkMeshBuilder::setBlockLibrary( blockLibrary );
}

void ThreadedChunkMeshBuilder::setTextureAtlas( const texture::TextureAtlas_sptr& textureAtlas ) {
	ChunkMeshBuilder::setTextureAtlas( textureAtlas );
}

void ThreadedChunkMeshBuilder::registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) {
	callback_ = callback;
}

void ThreadedChunkMeshBuilder::deregisterCallback() {
	callback_ = NULL;
}


}
}
