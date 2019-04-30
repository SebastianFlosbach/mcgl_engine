#pragma once

#include <functional>
#include <unordered_map>

#include "Coordinates/ChunkCoordinates.h"
#include "Chunk/Chunk.h"


namespace chunk {


enum class ChunkCollectionChangedEventType {
	ChunkAdded,
	ChunkRemoved
};

typedef std::function<void(const ChunkCollectionChangedEventType&, const ChunkCoordinates&)> CHUNK_COLLECTION_CHANGED_CALLBACK;

/**
	A collection of chunks
	\see Chunk
*/
class ChunkCollection {
public:

	/**
		Default constructor
	*/
	ChunkCollection() = default;

	/**
		Add a chunk to this collection.
		If a chunk already exists on this position it is overwritten.
		\param chunk Pointer to chunk data that will be moved
	*/
	void addChunk( chunk::Chunk_ptr&& chunk );

	/**
		Remove chunk from this collection
		\param position Position of the chunk to remove
	*/
	void removeChunk( const ChunkCoordinates& position );

	/**
		Get chunk from this collection.
		If the chunk does not exist nullptr is returned.
		\param position Position of the chunk
		\return Chunk at position or nullptr
	*/
	const chunk::Chunk* getChunk( const ChunkCoordinates& position ) const;

	/**
		Register a callback that is called whenever a chunk is added or removed.
		\param Callback that will be called
	*/
	void registerCollectionChangedCallback( CHUNK_COLLECTION_CHANGED_CALLBACK& callback );

	/**
		Deregister the collection changed callback.
		All further events are lost.
	*/
	void deregisterCollectionChangedCallback();

private:
	std::unordered_map<ChunkCoordinates, chunk::Chunk_ptr> chunks_;

	CHUNK_COLLECTION_CHANGED_CALLBACK collectionChangedCallback_;

};

typedef std::unique_ptr<ChunkCollection> ChunkCollection_ptr;


}
