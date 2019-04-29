#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "Helper/WorldChunkCoordinates.h"
#include "World/Chunk/Chunk.h"


namespace world {

	/**
		A collection of chunks to contain all information about this world
	*/
	class World {
	public:
		World() = default;

		World( const World& other ) = delete;
		World& operator=( const World& other ) = delete;

		World( World&& other ) noexcept;
		World& operator=( World&& other ) noexcept;

		/**
			Add a chunk to this world.
			If a chunk already exists on this position it is overwritten.
			\param chunk Chunk to add to this world
		*/
		void addChunk( const chunk::Chunk& chunk );

		/**
			Add a chunk to this world.
			If a chunk already exists on this position it is overwritten.
			\param chunk Pointer to chunk data that will be moved
		*/
		void addChunk( chunk::Chunk_ptr&& chunk );

		/**
			Remove chunk from this world
			\param position Position of the chunk to remove
		*/
		void removeChunk( const ChunkCoordinates& position );

		/**
			Get chunk from this world.
			If the chunk does not exist nullptr is returned.
			\param position Position of the chunk
			\return Chunk at position or nullptr
		*/
		const chunk::Chunk* getChunk( const ChunkCoordinates& position ) const;

	private:
		std::unordered_map<ChunkCoordinates, chunk::Chunk_ptr> worldChunks_;

	};


}