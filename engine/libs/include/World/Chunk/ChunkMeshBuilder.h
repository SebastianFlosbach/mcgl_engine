#pragma once

#include <vector>

#include "Chunk.h"
#include "../../Mesh/Mesh.h"

namespace world {
namespace chunk {


class ChunkMeshBuilder {
public:
	ChunkMeshBuilder() = default;

	Mesh createChunkMesh( const Chunk& chunk, const texture::TextureAtlas& textureAtlas ) {
		indexBase_ = 0;
		vertices_.clear();
		indices_.clear();

		for ( int x = 0; x < CHUNK_WIDTH; x++ ) {
			for ( int y = 0; y < CHUNK_HEIGHT; y++ ) {
				for ( int z = 0; z < CHUNK_LENGTH; z++ ) {
					const block::Block* block = chunk.getBlock( x, y, z );

					if ( block == nullptr || block->isTransparent_ ) {
						continue;
					}

					const block::Block* neighbour;

					// Left
					neighbour = chunk.getBlock( x - 1, y, z );
					if ( neighbour == nullptr || neighbour->isTransparent_ ) {
						auto texCoords = textureAtlas.getTextureCoords( block->leftTexture_ );

						vertices_.reserve( 4 );
						vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
						vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
						vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
						vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

						addIndices();
					}

					// Right
					neighbour = chunk.getBlock( x + 1, y, z );
					if ( neighbour == nullptr || neighbour->isTransparent_ ) {
						auto texCoords = textureAtlas.getTextureCoords( block->rightTexture_ );

						vertices_.reserve( 4 );
						vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
						vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
						vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
						vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

						addIndices();
					}

					// Bottom
					neighbour = chunk.getBlock( x, y - 1, z );
					if ( neighbour == nullptr || neighbour->isTransparent_ ) {
						auto texCoords = textureAtlas.getTextureCoords( block->bottomTexture_ );

						vertices_.reserve( 4 );
						vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
						vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
						vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
						vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

						addIndices();
					}

					// Top
					neighbour = chunk.getBlock( x, y + 1, z );
					if ( neighbour == nullptr || neighbour->isTransparent_ ) {
						auto texCoords = textureAtlas.getTextureCoords( block->topTexture_ );

						vertices_.reserve( 4 );
						vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
						vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
						vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
						vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

						addIndices();
					}

					// Front
					neighbour = chunk.getBlock( x, y, z - 1 );
					if ( neighbour == nullptr || neighbour->isTransparent_ ) {
						auto texCoords = textureAtlas.getTextureCoords( block->frontTexture_ );

						vertices_.reserve( 4 );
						vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
						vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
						vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
						vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

						addIndices();
					}

					// Back
					neighbour = chunk.getBlock( x, y, z + 1 );
					if ( neighbour == nullptr || neighbour->isTransparent_ ) {
						auto texCoords = textureAtlas.getTextureCoords( block->backTexture_ );

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

private:

	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;

	unsigned int indexBase_ = 0;

	void addIndices() {
		indices_.push_back( indexBase_ + 0 );
		indices_.push_back( indexBase_ + 1 );
		indices_.push_back( indexBase_ + 3 );
		indices_.push_back( indexBase_ + 1 );
		indices_.push_back( indexBase_ + 2 );
		indices_.push_back( indexBase_ + 3 );
		
		indexBase_ += 4;
	}

};


}
}
