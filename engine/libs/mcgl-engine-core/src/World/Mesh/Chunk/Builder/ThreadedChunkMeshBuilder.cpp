#include "World/Mesh/Chunk/Builder/ThreadedChunkMeshBuilder.h"

#include "World/Mesh/Chunk/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "World/World.h"
#include "World/Mesh/Chunk/Builder/ChunkMeshBuilder.h"

namespace world {
	namespace mesh {
namespace chunk {
namespace builder{


ThreadedChunkMeshBuilder::ThreadedChunkMeshBuilder( const logging::ILogger& logger, UNUM32 threadCount ) : ChunkMeshBuilder( logger ), threadPool_( threadCount ) {
}

ThreadedChunkMeshBuilder::ThreadedChunkMeshBuilder( const logging::ILogger& logger, const block::BlockLibrary* blockLibrary, texture::TextureLibrary* textureLibrary, UNUM32 threadCount ) :
	ChunkMeshBuilder( logger, blockLibrary, textureLibrary ),
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

void ThreadedChunkMeshBuilder::setBlockLibrary( const block::BlockLibrary* blockLibrary ) {
	ChunkMeshBuilder::setBlockLibrary( blockLibrary );
}

void ThreadedChunkMeshBuilder::setTextureLibrary( texture::TextureLibrary* textureLibrary ) {
	ChunkMeshBuilder::setTextureLibrary( textureLibrary );
}

void ThreadedChunkMeshBuilder::registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) {
	ChunkMeshBuilder::registerCallback( callback );
}

void ThreadedChunkMeshBuilder::deregisterCallback() {
	ChunkMeshBuilder::deregisterCallback();
}


}
}
	}
}
