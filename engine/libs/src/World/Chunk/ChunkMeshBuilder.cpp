#include "World/Chunk/ChunkMeshBuilder.h"


namespace world {
namespace chunk {


Mesh ChunkMeshBuilder::createChunkMesh( const Chunk& chunk, const texture::TextureAtlas& textureAtlas ) {
	indexBase_ = 0;
	vertices_.clear();
	indices_.clear();

	for ( int x = 0; x < CHUNK_WIDTH; x++ ) {
		for ( int y = 0; y < CHUNK_HEIGHT; y++ ) {
			for ( int z = 0; z < CHUNK_LENGTH; z++ ) {
				unsigned int blockId = chunk.getBlockId( x, y, z );

				if ( blockId == -1 || blockLibrary_.getBlock( blockId ).isTransparent_ ) {
					continue;
				}

				unsigned int neighbourId;

				// Left
				neighbourId = chunk.getBlockId( x - 1, y, z );
				if ( neighbourId == -1 || blockLibrary_.getBlock( neighbourId ).isTransparent_ ) {
					auto texCoords = textureAtlas.getTextureCoords( blockLibrary_.getBlock( blockId ).leftTexture_ );

					vertices_.reserve( 4 );
					vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
					vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
					vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
					vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

					addIndices();
				}

				// Right
				neighbourId = chunk.getBlockId( x + 1, y, z );
				if ( neighbourId == -1 || blockLibrary_.getBlock( neighbourId ).isTransparent_ ) {
					auto texCoords = textureAtlas.getTextureCoords( blockLibrary_.getBlock( blockId ).rightTexture_ );

					vertices_.reserve( 4 );
					vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
					vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
					vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
					vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

					addIndices();
				}

				// Bottom
				neighbourId = chunk.getBlockId( x, y - 1, z );
				if ( neighbourId == -1 || blockLibrary_.getBlock( neighbourId ).isTransparent_ ) {
					auto texCoords = textureAtlas.getTextureCoords( blockLibrary_.getBlock( blockId ).bottomTexture_ );

					vertices_.reserve( 4 );
					vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
					vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
					vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
					vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

					addIndices();
				}

				// Top
				neighbourId = chunk.getBlockId( x, y + 1, z );
				if ( neighbourId == -1 || blockLibrary_.getBlock( neighbourId ).isTransparent_ ) {
					auto texCoords = textureAtlas.getTextureCoords( blockLibrary_.getBlock( blockId ).topTexture_ );

					vertices_.reserve( 4 );
					vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
					vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
					vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
					vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

					addIndices();
				}

				// Front
				neighbourId = chunk.getBlockId( x, y, z - 1 );
				if ( neighbourId == -1 || blockLibrary_.getBlock( neighbourId ).isTransparent_ ) {
					auto texCoords = textureAtlas.getTextureCoords( blockLibrary_.getBlock( blockId ).frontTexture_ );

					vertices_.reserve( 4 );
					vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
					vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
					vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
					vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

					addIndices();
				}

				// Back
				neighbourId = chunk.getBlockId( x, y, z + 1 );
				if ( neighbourId == -1 || blockLibrary_.getBlock( neighbourId ).isTransparent_ ) {
					auto texCoords = textureAtlas.getTextureCoords( blockLibrary_.getBlock( blockId ).backTexture_ );

					vertices_.reserve( 4 );
					vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
					vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
					vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
					vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

					addIndices();
				}
			}
		}
	}

	return { std::move( vertices_ ), std::move( indices_ ), textureAtlas };
}


}
}