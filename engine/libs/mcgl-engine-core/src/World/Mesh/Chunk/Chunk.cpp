#include "Chunk/Chunk.h"

#include "Definition/mcgl_engine_def.h"

namespace world {
namespace mesh {
namespace chunk {

Chunk::Chunk( const coordinates::ChunkCoordinates& position ) : position_( position ) {}

void Chunk::setBlock( NUM32 x, NUM32 y, NUM32 z, const chunk::block::Block& block ) noexcept {
	setBlock( x, y, z, block.id_ );
}

void Chunk::setBlock( NUM32 x, NUM32 y, NUM32 z, NUM32 id ) noexcept {
	if( x < 0 || x >= CHUNK_WIDTH
		|| y < 0 || y >= CHUNK_HEIGHT
		|| z < 0 || z >= CHUNK_LENGTH ) {
		return;
	}

	blocks_[x][y][z] = id;
}

UNUM32 Chunk::getBlockId( NUM32 x, NUM32 y, NUM32 z ) const noexcept {
	if( x < 0 || x >= CHUNK_WIDTH
		|| y < 0 || y >= CHUNK_HEIGHT
		|| z < 0 || z >= CHUNK_LENGTH ) {
		return BLOCK_DEFAULT_ID;
	}

	return blocks_[x][y][z];
}

void Chunk::setPosition( const coordinates::ChunkCoordinates& position ) {
	position_ = position;
}

const coordinates::ChunkCoordinates& Chunk::getPosition() const {
	return position_;
}

}
}
}
