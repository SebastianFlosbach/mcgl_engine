#include "Chunk/ChunkCollection.h"


namespace chunk {


void ChunkCollection::addChunk( chunk::Chunk_ptr&& chunk ) {
	auto position = chunk->getPosition();

	chunks_.insert( { position, std::move( chunk ) } );

	if ( collectionChangedCallback_ ) {
		collectionChangedCallback_( ChunkCollectionChangedEventType::ChunkAdded, position );
	}
}

void ChunkCollection::removeChunk( const ChunkCoordinates& position ) {
	chunks_.erase( position );

	if ( collectionChangedCallback_ ) {
		collectionChangedCallback_( ChunkCollectionChangedEventType::ChunkRemoved, position );
	}
}

const chunk::Chunk* ChunkCollection::getChunk( const ChunkCoordinates& position ) const {
	auto it = chunks_.find( position );

	if ( it != chunks_.end() ) {
		return it->second.get();
	}

	return nullptr;
}

void ChunkCollection::registerCollectionChangedCallback( CHUNK_COLLECTION_CHANGED_CALLBACK& callback ) {
	collectionChangedCallback_ = callback;
}

void ChunkCollection::deregisterCollectionChangedCallback() {
	collectionChangedCallback_ = NULL;
}


}
