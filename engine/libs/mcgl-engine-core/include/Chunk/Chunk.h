#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Chunk/Block/Block.h"
#include "Coordinates/ChunkCoordinates.h"


namespace chunk {

	/**
		A chunk of the world
	*/
	struct Chunk {
	public:

		/**
			Create chunk at position 0,0
		*/
		Chunk() = default;

		/**
			Create chunk at position
			\param position Position of the chunk
		*/
		Chunk( const coordinates::ChunkCoordinates& position );

		//Chunk( Chunk&& other ) noexcept;
		//Chunk& operator=( Chunk&& other ) noexcept;

		/**
			Set a block inside chunk space.
			Only the blocks id is safed, so any change to the blocks data will affect all blocks of that type in the chunk.
			Invalid coordinates are ignored.
			\param x X coordinate inside the chunk
			\param y Y coordinate inside the chunk
			\param z Z coordinate inside the chunk
			\param block Block data to set
		*/
		void setBlock( NUM32 x, NUM32 y, NUM32 z, const block::Block& block ) noexcept;

		void setBlock( NUM32 x, NUM32 y, NUM32 z, NUM32 id ) noexcept;

		/**
			Get the block id at a position inside this chunk.
			If the block wasn't set before, 0 is returned.
			Invalid coordinates return <DEFAULT_ID>
			\param x X coordinate inside the chunk
			\param y Y coordinate inside the chunk
			\param z Z coordinate inside the chunk
			\return Id of the specified block
		*/
		UNUM32 getBlockId( NUM32 x, NUM32 y, NUM32 z ) const noexcept;

		/*
			Set the position of this chunk inside the world
			\param position New coordinates for this chunk
		*/
		void setPosition( const coordinates::ChunkCoordinates& position );

		/**
			Get the position of this chunk inside the world
			\return Coordinates of this chunk
		*/
		const coordinates::ChunkCoordinates& getPosition() const;

	private:
		static const UNUM32 DEFAULT_ID;

		UNUM32 blocks_[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH]{ 0 };
		coordinates::ChunkCoordinates position_{ 0, 0 };

	};

	typedef std::unique_ptr<Chunk> Chunk_ptr;
}
