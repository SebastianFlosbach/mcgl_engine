#include "Chunk/Builder/ChunkMeshBuilder.h"

#include "World/World.h"
#include "Chunk/Block/BlockLibrary.h"
#include "Chunk/Chunk.h"


namespace chunk {
namespace builder {


ChunkMeshBuilder::ChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas ) :
	pBlockLibrary_( blockLibrary ), pTextureAtlas_( textureAtlas ) {
}

void ChunkMeshBuilder::setBlockLibrary( const block::BlockLibrary_sptr& blockLibrary ) {
	pBlockLibrary_ = blockLibrary;
}

void ChunkMeshBuilder::setTextureAtlas( const texture::TextureAtlas_sptr& textureAtlas ) {
	pTextureAtlas_ = textureAtlas;
}

void ChunkMeshBuilder::addIndices() {
	indices_.push_back( indexBase_ + 0 );
	indices_.push_back( indexBase_ + 1 );
	indices_.push_back( indexBase_ + 3 );
	indices_.push_back( indexBase_ + 1 );
	indices_.push_back( indexBase_ + 2 );
	indices_.push_back( indexBase_ + 3 );

	indexBase_ += 4;
}

void ChunkMeshBuilder::left		( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	// Check neighbouring chunk
	if( x == 0 ) {
		auto* neighbourChunk = chunks.getChunk( position.x_ - 1, position.z_ );
		if( neighbourChunk != nullptr ) {
			neighbourId = neighbourChunk->getBlockId( CHUNK_WIDTH - 1, y, z );
		}
	}
	else {
		neighbourId = chunk.getBlockId( x - 1, y, z );
	}

	if( neighbourId == BLOCK_DEFAULT_ID || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).leftTextureId_ );

		vertices_.reserve( 4 );
		vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
		vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
		vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
		vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

		addIndices();
	}
}
								  		   	
void ChunkMeshBuilder::right	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	if( x == CHUNK_WIDTH - 1 ) {
		auto* neighbourChunk = chunks.getChunk( position.x_ + 1, position.z_ );
		if( neighbourChunk != nullptr ) {
			neighbourId = neighbourChunk->getBlockId( 0, y, z );
		}
	}
	else {
		neighbourId = chunk.getBlockId( x + 1, y, z );
	}

	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).rightTextureId_ );

		vertices_.reserve( 4 );
		vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
		vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
		vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
		vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

		addIndices();
	}
}
								  		   	
void ChunkMeshBuilder::top		( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	neighbourId = chunk.getBlockId( x, y + 1, z );
	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).topTextureId_ );

		vertices_.reserve( 4 );
		vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
		vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
		vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
		vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

		addIndices();
	}
}
								  		   	
void ChunkMeshBuilder::bottom	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	neighbourId = chunk.getBlockId( x, y - 1, z );
	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).bottomTextureId_ );

		vertices_.reserve( 4 );
		vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
		vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
		vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
		vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

		addIndices();
	}
}
								  		   	
void ChunkMeshBuilder::front	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	if( z == 0 ) {
		auto* neighbourChunk = chunks.getChunk( position.x_, position.z_ - 1 );
		if( neighbourChunk != nullptr ) {
			neighbourId = neighbourChunk->getBlockId( x, y, CHUNK_LENGTH - 1 );
		}
	}
	else {
		neighbourId = chunk.getBlockId( x, y, z - 1 );
	}

	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).frontTextureId_ );

		vertices_.reserve( 4 );
		vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
		vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
		vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
		vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

		addIndices();
	}
}
								  		   	
void ChunkMeshBuilder::back		( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	if( z == CHUNK_LENGTH - 1 ) {
		auto* neighbourChunk = chunks.getChunk( position.x_, position.z_ + 1 );
		if( neighbourChunk != nullptr ) {
			neighbourId = neighbourChunk->getBlockId( x, y, 0 );
		}
	}
	else {
		neighbourId = chunk.getBlockId( x, y, z + 1 );
	}

	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).backTextureId_ );

		vertices_.reserve( 4 );
		vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
		vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
		vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
		vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

		addIndices();
	}
}

mesh::Mesh* ChunkMeshBuilder::build( const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks ) {
	if( !pBlockLibrary_ || !pTextureAtlas_ ) {
		return nullptr;
	}

	indexBase_ = 0;
	vertices_.clear();
	indices_.clear();

	auto* chunk_ptr = chunks.getChunk( position );
	if( chunk_ptr == nullptr ) {
		throw std::runtime_error( "Could not create mesh. Chunk does not exist" );
	}

	auto& chunk = *chunk_ptr;

	for( int x = 0; x < CHUNK_WIDTH; x++ ) {
		for( int y = 0; y < CHUNK_HEIGHT; y++ ) {
			for( int z = 0; z < CHUNK_LENGTH; z++ ) {
				unsigned int blockId = chunk.getBlockId( x, y, z );

				if( blockId == BLOCK_DEFAULT_ID || pBlockLibrary_->getBlock( blockId ).isTransparent_ ) {
					continue;
				}

				left	( x, y, z, position, chunks, chunk, blockId );
				right	( x, y, z, position, chunks, chunk, blockId );
				bottom	( x, y, z, position, chunks, chunk, blockId );
				top		( x, y, z, position, chunks, chunk, blockId );
				front	( x, y, z, position, chunks, chunk, blockId );
				back	( x, y, z, position, chunks, chunk, blockId );

			}
		}
	}

	return new mesh::Mesh( std::move( vertices_ ), std::move( indices_ ) );
}


}
}
