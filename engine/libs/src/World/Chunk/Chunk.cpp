#include "World/Chunk/Chunk.h"
#include <stdexcept>


namespace world {
	namespace chunk{
	
		const UNUM32 Chunk::DEFAULT_ID = 0;

		Chunk::Chunk( const ChunkCoordinates& position ) : position_( position ) {}

		void Chunk::setBlock( NUM32 x, NUM32 y, NUM32 z, const block::Block& block ) {
			if( x < 0 || x >= CHUNK_WIDTH
				|| y < 0 || y >= CHUNK_HEIGHT
				|| z < 0 || z >= CHUNK_LENGTH ) {
				return;
			}

			blocks_[x][y][z] = block.id_;
		}

		UNUM32 Chunk::getBlockId( NUM32 x, NUM32 y, NUM32 z ) const {
			if( x < 0 || x >= CHUNK_WIDTH
				|| y < 0 || y >= CHUNK_HEIGHT
				|| z < 0 || z >= CHUNK_LENGTH ) {
				return DEFAULT_ID;
			}

			return blocks_[x][y][z];
		}

		void Chunk::setPosition( const ChunkCoordinates& position ) {
			position_ = position;
		}

		const ChunkCoordinates& Chunk::getPosition() const {
			return position_;
		}

	}
}