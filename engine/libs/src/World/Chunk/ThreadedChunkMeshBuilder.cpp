#include "World/Chunk/ThreadedChunkMeshBuilder.h"

#include "World/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "World/World.h"
#include "World/Chunk/ChunkMeshBuilder.h"

namespace world {
	namespace chunk {

		ThreadedChunkMeshBuilder::ThreadedChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas, const unsigned int threadCount ) :
			threadPool_( threadCount ),
			pChunkMeshBuilder_( new ChunkMeshBuilder( blockLibrary, textureAtlas ) ) {
		}

		void ThreadedChunkMeshBuilder::createChunkMesh( int x, int z, world::World& world, CHUNK_MESH_BUILDER_CALLBACK callback ) {
			threadPool_.push( [this, &x, &z, &world, &callback]( int id ) {
				auto mesh = std::unique_ptr<Mesh>( pChunkMeshBuilder_->createChunkMesh( x, z, world ) );
				callback( { x, z }, std::move( mesh ) );
				} );
		}

	}
}