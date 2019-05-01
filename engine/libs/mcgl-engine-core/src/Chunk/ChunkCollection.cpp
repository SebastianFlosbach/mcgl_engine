#include "Chunk/ChunkCollection.h"

#include "Coordinates/ChunkCoordinates.h"


namespace chunk {


void ChunkCollection::addChunk( chunk::Chunk_ptr&& chunk ) {
	auto position = chunk->getPosition();

	chunks_.insert( { position, std::move( chunk ) } );

	if ( collectionChangedCallback_ ) {
		collectionChangedCallback_( ChunkCollectionChangedEventType::ChunkAdded, position );
	}
}

void ChunkCollection::removeChunk( const coordinates::ChunkCoordinates& position ) {
	chunks_.erase( position );

	if ( collectionChangedCallback_ ) {
		collectionChangedCallback_( ChunkCollectionChangedEventType::ChunkRemoved, position );
	}
}

const chunk::Chunk* ChunkCollection::getChunk( const coordinates::ChunkCoordinates& position ) const {
	auto it = chunks_.find( position );

	if ( it != chunks_.end() ) {
		return it->second.get();
	}

	return nullptr;
}

const chunk::Chunk* ChunkCollection::getChunk( NUM32 x, NUM32 z ) const {
	return getChunk( { x, z } );
}

void ChunkCollection::registerCollectionChangedCallback( CHUNK_COLLECTION_CHANGED_CALLBACK& callback ) {
	collectionChangedCallback_ = callback;
}

void ChunkCollection::deregisterCollectionChangedCallback() {
	collectionChangedCallback_ = NULL;
}


}
