#include "Chunk/Builder/ThreadedChunkMeshBuilder.h"

#include "Chunk/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "World/World.h"
#include "Chunk/Builder/ChunkMeshBuilder.h"


namespace chunk {
namespace builder{


ThreadedChunkMeshBuilder::ThreadedChunkMeshBuilder( const ILogger& logger, UNUM32 threadCount ) : logger_( logger ), threadPool_( threadCount ) {
}

ThreadedChunkMeshBuilder::ThreadedChunkMeshBuilder( const ILogger& logger, const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas, UNUM32 threadCount ) :
	ChunkMeshBuilder( blockLibrary, textureAtlas ),
	logger_( logger ),
	threadPool_( threadCount ) {
}

void ThreadedChunkMeshBuilder::build( const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks ) {
	debug( logger_, std::string( "Building mesh at position " ) + position.to_string() );
	
	threadPool_.push( [this, position, &chunks]( int id ) {
		ChunkMeshBuilder::build( position, chunks );
	} );

	//NUM32 x = position.x_;
	//NUM32 z = position.z_;

	/*threadPool_.push( [this, x, z, &chunks]( int id ) {
		auto pos = coordinates::ChunkCoordinates( x + 1, z );
		ChunkMeshBuilder::build( pos, chunks );
	} );

	threadPool_.push( [this, x, z, &chunks]( int id ) {
		auto pos = coordinates::ChunkCoordinates( x - 1, z );
		ChunkMeshBuilder::build( pos, chunks );
	} );

	threadPool_.push( [this, x, z, &chunks]( int id ) {
		auto pos = coordinates::ChunkCoordinates( x, z + 1 );
		ChunkMeshBuilder::build( pos, chunks );
	} );

	threadPool_.push( [this, x, z, &chunks]( int id ) {
		auto pos = coordinates::ChunkCoordinates( x, z - 1 );
		ChunkMeshBuilder::build( pos, chunks );
	} );*/
}

void ThreadedChunkMeshBuilder::setBlockLibrary( const block::BlockLibrary_sptr& blockLibrary ) {
	ChunkMeshBuilder::setBlockLibrary( blockLibrary );
}

void ThreadedChunkMeshBuilder::setTextureAtlas( const texture::TextureAtlas_sptr& textureAtlas ) {
	ChunkMeshBuilder::setTextureAtlas( textureAtlas );
}

void ThreadedChunkMeshBuilder::registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) {
	ChunkMeshBuilder::registerCallback( callback );
}

void ThreadedChunkMeshBuilder::deregisterCallback() {
	ChunkMeshBuilder::deregisterCallback();
}


}
}
