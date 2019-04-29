#include "World/Chunk/Builder/ChunkMeshBuilder.h"

#include "World/World.h"
#include "World/Block/BlockLibrary.h"
#include "World/Chunk/Chunk.h"


namespace world {
	namespace chunk {

		ChunkMeshBuilder::ChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas ) :
			blockLibrary_( blockLibrary ), textureAtlas_( textureAtlas ) {
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

		void ChunkMeshBuilder::left( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World& world, const Chunk& chunk, const texture::TextureAtlas& textureAtlas, const unsigned int blockId ) {
			if( x == 0 ) {
				auto* neighbourChunk = world.getChunk( xChunk - 1, zChunk );
				if( neighbourChunk != nullptr ) {
					neighbourId = neighbourChunk->getBlockId( CHUNK_WIDTH - 1, y, z );
				} else {
					neighbourId = -1;
				}
			} else {
				neighbourId = chunk.getBlockId( x - 1, y, z );
			}

			if( neighbourId == -1 || blockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
				auto texCoords = textureAtlas.getTextureCoords( blockLibrary_->getBlock( blockId ).leftTexture_ );

				vertices_.reserve( 4 );
				vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
				vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
				vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
				vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

				addIndices();
			}
		}

		void ChunkMeshBuilder::right( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World& world, const Chunk& chunk, const texture::TextureAtlas& textureAtlas, const unsigned int blockId ) {
			if( x == CHUNK_WIDTH - 1 ) {
				auto* neighbourChunk = world.getChunk( xChunk + 1, zChunk );
				if( neighbourChunk != nullptr ) {
					neighbourId = neighbourChunk->getBlockId( 0, y, z );
				} else {
					neighbourId = -1;
				}
			} else {
				neighbourId = chunk.getBlockId( x + 1, y, z );
			}

			if( neighbourId == -1 || blockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
				auto texCoords = textureAtlas.getTextureCoords( blockLibrary_->getBlock( blockId ).rightTexture_ );

				vertices_.reserve( 4 );
				vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
				vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
				vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
				vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

				addIndices();
			}
		}

		void ChunkMeshBuilder::top( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World& world, const Chunk& chunk, const texture::TextureAtlas& textureAtlas, const unsigned int blockId ) {
			neighbourId = chunk.getBlockId( x, y + 1, z );
			if( neighbourId == -1 || blockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
				auto texCoords = textureAtlas.getTextureCoords( blockLibrary_->getBlock( blockId ).topTexture_ );

				vertices_.reserve( 4 );
				vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
				vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
				vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
				vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

				addIndices();
			}
		}

		void ChunkMeshBuilder::bottom( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World& world, const Chunk& chunk, const texture::TextureAtlas& textureAtlas, const unsigned int blockId ) {
			neighbourId = chunk.getBlockId( x, y - 1, z );
			if( neighbourId == -1 || blockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
				auto texCoords = textureAtlas.getTextureCoords( blockLibrary_->getBlock( blockId ).bottomTexture_ );

				vertices_.reserve( 4 );
				vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
				vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
				vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
				vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

				addIndices();
			}
		}

		void ChunkMeshBuilder::front( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World& world, const Chunk& chunk, const texture::TextureAtlas& textureAtlas, const unsigned int blockId ) {
			if( z == 0 ) {
				auto* neighbourChunk = world.getChunk( xChunk, zChunk - 1 );
				if( neighbourChunk != nullptr ) {
					neighbourId = neighbourChunk->getBlockId( x, y, CHUNK_LENGTH - 1 );
				} else {
					neighbourId = -1;
				}
			} else {
				neighbourId = chunk.getBlockId( x, y, z - 1 );
			}

			if( neighbourId == -1 || blockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
				auto texCoords = textureAtlas.getTextureCoords( blockLibrary_->getBlock( blockId ).frontTexture_ );

				vertices_.reserve( 4 );
				vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 0.0f }, { texCoords[0], texCoords[1] } } );
				vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 0.0f }, { texCoords[2], texCoords[3] } } );
				vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 0.0f }, { texCoords[4], texCoords[5] } } );
				vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 0.0f }, { texCoords[6], texCoords[7] } } );

				addIndices();
			}
		}

		void ChunkMeshBuilder::back( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World& world, const Chunk& chunk, const texture::TextureAtlas& textureAtlas, const unsigned int blockId ) {
			if( z == CHUNK_LENGTH - 1 ) {
				auto* neighbourChunk = world.getChunk( xChunk, zChunk + 1 );
				if( neighbourChunk != nullptr ) {
					neighbourId = neighbourChunk->getBlockId( x, y, 0 );
				} else {
					neighbourId = -1;
				}
			} else {
				neighbourId = chunk.getBlockId( x, y, z + 1 );
			}

			if( neighbourId == -1 || blockLibrary_->getBlock( neighbourId ).isTransparent_ ) {
				auto texCoords = textureAtlas.getTextureCoords( blockLibrary_->getBlock( blockId ).backTexture_ );

				vertices_.reserve( 4 );
				vertices_.push_back( { { x + 1.0f, y + 0.0f, z + 1.0f }, { texCoords[0], texCoords[1] } } );
				vertices_.push_back( { { x + 0.0f, y + 0.0f, z + 1.0f }, { texCoords[2], texCoords[3] } } );
				vertices_.push_back( { { x + 0.0f, y + 1.0f, z + 1.0f }, { texCoords[4], texCoords[5] } } );
				vertices_.push_back( { { x + 1.0f, y + 1.0f, z + 1.0f }, { texCoords[6], texCoords[7] } } );

				addIndices();
			}
		}

		mesh::Mesh* ChunkMeshBuilder::build( const int xChunk, const int zChunk, const World& world ) {
			indexBase_ = 0;
			vertices_.clear();
			indices_.clear();

			auto* chunk_ptr = world.getChunk( xChunk, zChunk );
			if( chunk_ptr == nullptr ) {
				throw std::runtime_error( "Could not create mesh. Chunk does not exist" );
			}

			auto chunk = *chunk_ptr;

			for( int x = 0; x < CHUNK_WIDTH; x++ ) {
				for( int y = 0; y < CHUNK_HEIGHT; y++ ) {
					for( int z = 0; z < CHUNK_LENGTH; z++ ) {
						unsigned int blockId = chunk.getBlockId( x, y, z );

						if( blockId == -1 || blockLibrary_->getBlock( blockId ).isTransparent_ ) {
							continue;
						}

						unsigned int neighbourId = 0;

						left( x, y, z, xChunk, zChunk, neighbourId, world, chunk, *textureAtlas_.get(), blockId );
						right( x, y, z, xChunk, zChunk, neighbourId, world, chunk, *textureAtlas_.get(), blockId );
						bottom( x, y, z, xChunk, zChunk, neighbourId, world, chunk, *textureAtlas_.get(), blockId );
						top( x, y, z, xChunk, zChunk, neighbourId, world, chunk, *textureAtlas_.get(), blockId );
						front( x, y, z, xChunk, zChunk, neighbourId, world, chunk, *textureAtlas_.get(), blockId );
						back( x, y, z, xChunk, zChunk, neighbourId, world, chunk, *textureAtlas_.get(), blockId );

					}
				}
			}

			return new Mesh( std::move( vertices_ ), std::move( indices_ ), *textureAtlas_.get(), { chunk.getPosition().x_ * (int)CHUNK_WIDTH, 0.0, chunk.getPosition().z_ * (int)CHUNK_LENGTH } );
		}


	}
}