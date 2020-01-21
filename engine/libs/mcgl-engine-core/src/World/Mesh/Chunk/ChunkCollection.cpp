#include "World/Mesh/Chunk/ChunkCollection.h"

#include "Coordinates/ChunkCoordinates.h"


namespace world {
	namespace mesh {
		namespace chunk {


void ChunkCollection::addChunk( chunk::Chunk_ptr&& chunk ) {
	auto position = chunk->getPosition();

	std::lock_guard<std::mutex> lock( mChunks_ );

	chunks_.insert( { position, std::move( chunk ) } );

	if ( collectionChangedCallback_ ) {
		collectionChangedCallback_( ChunkCollectionChangedEventType::ChunkAdded, position );
	}
}

void ChunkCollection::removeChunk( const coordinates::ChunkCoordinates& position ) {
	std::lock_guard<std::mutex> lock( mChunks_ );

	chunks_.erase( position );

	if ( collectionChangedCallback_ ) {
		collectionChangedCallback_( ChunkCollectionChangedEventType::ChunkRemoved, position );
	}
}

const chunk::Chunk_sptr ChunkCollection::getChunk( const coordinates::ChunkCoordinates& position ) const {
	std::lock_guard<std::mutex> lock( mChunks_ );

	auto it = chunks_.find( position );

	if ( it != chunks_.end() ) {
		return it->second;
	}

	return nullptr;
}

const chunk::Chunk_sptr ChunkCollection::getChunk( NUM32 x, NUM32 z ) const {
	return getChunk( { x, z } );
}

void ChunkCollection::registerCollectionChangedCallback( CHUNK_COLLECTION_CHANGED_CALLBACK& callback ) {
	collectionChangedCallback_ = callback;
}

void ChunkCollection::deregisterCollectionChangedCallback() {
	collectionChangedCallback_ = NULL;
}


}
	}
}
