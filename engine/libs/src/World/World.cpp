#include "World/World.h"

#include "World/Chunk/Chunk.h"
#include ""

namespace world {

	World::World( const block::BlockLibrary& blockLibrary, const texture::TextureAtlas& textureAtlas ) : pChunkMeshBuilder_( new chunk::ThreadedChunkMeshBuilder( blockLibrary, textureAtlas, 4 ) ) {}

	void World::addChunk( const chunk::Chunk& chunk ) {
		worldChunks_.insert( { { chunk.getPosition().x_, chunk.getPosition().z_ }, chunk } );

		auto& position = chunk.getPosition();

		auto x = position.x_;
		auto z = position.z_;

		if( worldChunks_.find( { x + 1, z } ) != worldChunks_.end() ) {
			removeMesh( { x + 1, z } );
			pChunkMeshBuilder_->createChunkMesh( x + 1, z, *this, std::bind( &World::addMesh, this, std::placeholders::_1, std::placeholders::_2 ) );
		}

		if( worldChunks_.find( { x - 1, z } ) != worldChunks_.end() ) {
			removeMesh( { x - 1, z } );
			pChunkMeshBuilder_->createChunkMesh( x - 1, z, *this, std::bind( &World::addMesh, this, std::placeholders::_1, std::placeholders::_2 ) );
		}

		if( worldChunks_.find( { x, z + 1 } ) != worldChunks_.end() ) {
			removeMesh( { x, z + 1 } );
			pChunkMeshBuilder_->createChunkMesh( x, z + 1, *this, std::bind( &World::addMesh, this, std::placeholders::_1, std::placeholders::_2 ) );
		}

		if( worldChunks_.find( { x, z - 1 } ) != worldChunks_.end() ) {
			removeMesh( { x, z - 1 } );
			pChunkMeshBuilder_->createChunkMesh( x, z - 1, *this, std::bind( &World::addMesh, this, std::placeholders::_1, std::placeholders::_2 ) );
		}

		pChunkMeshBuilder_->createChunkMesh( x, z, *this, std::bind( &World::addMesh, this, std::placeholders::_1, std::placeholders::_2 ) );
	}
}