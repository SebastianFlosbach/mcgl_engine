#include "Chunk/Builder/ChunkMeshBuilder.h"

#include "World/World.h"
#include "Chunk/Block/BlockLibrary.h"
#include "Chunk/Chunk.h"


namespace chunk {
namespace builder {

ChunkMeshBuilder::ChunkMeshBuilder( const logging::ILogger& logger ) : logger_( logger ) {
}

ChunkMeshBuilder::ChunkMeshBuilder( const logging::ILogger& logger, const block::BlockLibrary* blockLibrary, const texture::TextureAtlas_sptr& textureAtlas ) :
	logger_( logger ), pBlockLibrary_( blockLibrary ), pTextureAtlas_( textureAtlas ) {
}

void ChunkMeshBuilder::setBlockLibrary( const block::BlockLibrary* blockLibrary ) {
	pBlockLibrary_ = blockLibrary;
}

void ChunkMeshBuilder::setTextureAtlas( const texture::TextureAtlas_sptr& textureAtlas ) {
	pTextureAtlas_ = textureAtlas;
}

void ChunkMeshBuilder::addIndices( std::vector<UNUM32>& indices, UNUM32& indexBase ) {
	indices.push_back( indexBase + 0 );
	indices.push_back( indexBase + 1 );
	indices.push_back( indexBase + 3 );
	indices.push_back( indexBase + 1 );
	indices.push_back( indexBase + 2 );
	indices.push_back( indexBase + 3 );

	indexBase += 4;
}

void ChunkMeshBuilder::left		( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	// Check neighbouring chunk
	if( x == 0 ) {
		auto neighbourChunk = chunks.getChunk( position.x_ - 1, position.z_ );
		if( neighbourChunk != nullptr ) {
			neighbourId = neighbourChunk->getBlockId( CHUNK_WIDTH - 1, y, z );
		}
	}
	else {
		neighbourId = chunk.getBlockId( x - 1, y, z );
	}

	if( neighbourId == BLOCK_DEFAULT_ID || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).leftTextureId_ );

		vertices.reserve( 4 );
		vertices.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
		vertices.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
		vertices.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
		vertices.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

		addIndices( indices, indexBase );
	}
}
								  		   																																	  					  										  
void ChunkMeshBuilder::right	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	if( x == CHUNK_WIDTH - 1 ) {
		auto neighbourChunk = chunks.getChunk( position.x_ + 1, position.z_ );
		if( neighbourChunk != nullptr ) {
			neighbourId = neighbourChunk->getBlockId( 0, y, z );
		}
	}
	else {
		neighbourId = chunk.getBlockId( x + 1, y, z );
	}

	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).rightTextureId_ );

		vertices.reserve( 4 );
		vertices.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
		vertices.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
		vertices.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
		vertices.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

		addIndices( indices, indexBase );
	}
}
								  		   																																	  					  										  
void ChunkMeshBuilder::top		( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	neighbourId = chunk.getBlockId( x, y + 1, z );
	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).topTextureId_ );

		vertices.reserve( 4 );
		vertices.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
		vertices.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
		vertices.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
		vertices.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

		addIndices( indices, indexBase );
	}
}
								  		   																																	 					 										  
void ChunkMeshBuilder::bottom	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	neighbourId = chunk.getBlockId( x, y - 1, z );
	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).bottomTextureId_ );

		vertices.reserve( 4 );
		vertices.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
		vertices.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
		vertices.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
		vertices.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

		addIndices( indices, indexBase );
	}
}
								  		   																																	 					  										  
void ChunkMeshBuilder::front	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	if( z == 0 ) {
		auto neighbourChunk = chunks.getChunk( position.x_, position.z_ - 1 );
		if( neighbourChunk != nullptr ) {
			neighbourId = neighbourChunk->getBlockId( x, y, CHUNK_LENGTH - 1 );
		}
	}
	else {
		neighbourId = chunk.getBlockId( x, y, z - 1 );
	}

	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).frontTextureId_ );

		vertices.reserve( 4 );
		vertices.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
		vertices.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
		vertices.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
		vertices.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

		addIndices( indices, indexBase );
	}
}
								  		   																																	 					  										  
void ChunkMeshBuilder::back		( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase ) {
	UNUM32 neighbourId = BLOCK_DEFAULT_ID;
	
	if( z == CHUNK_LENGTH - 1 ) {
		auto neighbourChunk = chunks.getChunk( position.x_, position.z_ + 1 );
		if( neighbourChunk != nullptr ) {
			neighbourId = neighbourChunk->getBlockId( x, y, 0 );
		}
	}
	else {
		neighbourId = chunk.getBlockId( x, y, z + 1 );
	}

	if( neighbourId == -1 || pBlockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
		auto texCoords = pTextureAtlas_->getTextureCoords( pBlockLibrary_->getBlock( blockId ).backTextureId_ );

		vertices.reserve( 4 );
		vertices.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
		vertices.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
		vertices.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
		vertices.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

		addIndices( indices, indexBase );
	}
}

void ChunkMeshBuilder::build( const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks ) {
	if( !pBlockLibrary_ ) {
		error( logger_, std::string( __FUNCTION__ ) + ": Could not create mesh, block library is missing!" );
		return;
	}

	if( !pTextureAtlas_ ) {
		error( logger_, std::string( __FUNCTION__ ) + ": Could not create mesh, texture atlas is missing!" );
		return;
	}

	std::vector<Vertex> vertices;
	std::vector<UNUM32> indices;
	UNUM32 indexBase = 0;

	auto chunk_ptr = chunks.getChunk( position );
	if( chunk_ptr == nullptr ) {
		//throw std::runtime_error( "Could not create mesh. Chunk does not exist" );
		error( logger_, std::string( __FUNCTION__ ) + ": Could not create mesh, chunk does not exist!" );
		return;
	}

	auto& chunk = *chunk_ptr;

	for( int x = 0; x < CHUNK_WIDTH; x++ ) {
		for( int y = 0; y < CHUNK_HEIGHT; y++ ) {
			for( int z = 0; z < CHUNK_LENGTH; z++ ) {
				unsigned int blockId = chunk.getBlockId( x, y, z );

				if( blockId == BLOCK_DEFAULT_ID || pBlockLibrary_->getBlock( blockId ).isTransparent_ ) {
					continue;
				}

				left	( x, y, z, position, chunks, chunk, blockId, vertices, indices, indexBase );
				right	( x, y, z, position, chunks, chunk, blockId, vertices, indices, indexBase );
				bottom	( x, y, z, position, chunks, chunk, blockId, vertices, indices, indexBase );
				top		( x, y, z, position, chunks, chunk, blockId, vertices, indices, indexBase );
				front	( x, y, z, position, chunks, chunk, blockId, vertices, indices, indexBase );
				back	( x, y, z, position, chunks, chunk, blockId, vertices, indices, indexBase );

			}
		}
	}

	if( callback_ ) {
		callback_( position, new mesh::Mesh( std::move( vertices ), std::move( indices ) ) );
	}
}

void ChunkMeshBuilder::registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) {
	callback_ = callback;
}

void ChunkMeshBuilder::deregisterCallback() {
	callback_ = NULL;
}

}
}
