#include "World/World.h"


namespace world {

	World::World( World&& other ) {
		if( this == &other ) {
			return;
		}

		this->worldChunks_ = std::move( other.worldChunks_ );
	}

	World& World::operator=( World&& other ) {
		return std::move( other );
	}

	void World::addChunk( const chunk::Chunk& chunk ) {
		worldChunks_.insert( { chunk.getPosition(), std::make_unique<chunk::Chunk>( chunk ) } );

		/*auto& position = chunk.getPosition();

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

		pChunkMeshBuilder_->createChunkMesh( x, z, *this, std::bind( &World::addMesh, this, std::placeholders::_1, std::placeholders::_2 ) );*/
	}

	void World::addChunk( chunk::Chunk_ptr&& chunk ) {
		worldChunks_.insert( { chunk->getPosition(), std::move( chunk ) } );
	}

	void World::removeChunk( const ChunkCoordinates& position ) {
		worldChunks_.erase( position );
	}

	const chunk::Chunk* World::getChunk( const ChunkCoordinates& position ) const {
		auto it = worldChunks_.find( position );

		if( it != worldChunks_.end() ) {
			return &it->second;
		}

		return nullptr;
	}

}