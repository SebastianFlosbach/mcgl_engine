#pragma once

#include <vector>
#include <memory>

#include "World/Chunk/Chunk.h"
#include "World/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"


class Mesh;
struct Vertex;

namespace world {
	class World;

	namespace chunk {

		class ChunkMeshBuilder {
		public:
			ChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas );

			Mesh* createChunkMesh( const int x, const int z, const World& world );

		private:

			std::vector<Vertex> vertices_;
			std::vector<unsigned int> indices_;

			const block::BlockLibrary_sptr blockLibrary_;
			const texture::TextureAtlas_sptr textureAtlas_;

			unsigned int indexBase_ = 0;

			inline void addIndices();

			inline void left( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World & world, const Chunk & chunk, const texture::TextureAtlas & textureAtlas, const unsigned int blockId );
			inline void right( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World & world, const Chunk & chunk, const texture::TextureAtlas & textureAtlas, const unsigned int blockId );
			inline void top( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World & world, const Chunk & chunk, const texture::TextureAtlas & textureAtlas, const unsigned int blockId );
			inline void bottom( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World & world, const Chunk & chunk, const texture::TextureAtlas & textureAtlas, const unsigned int blockId );
			inline void front( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World & world, const Chunk & chunk, const texture::TextureAtlas & textureAtlas, const unsigned int blockId );
			inline void back( const int x, const int y, const int z, const int xChunk, const int zChunk, unsigned int& neighbourId, const World & world, const Chunk & chunk, const texture::TextureAtlas & textureAtlas, const unsigned int blockId );

		};

		typedef std::unique_ptr<ChunkMeshBuilder> ChunkMeshBuilder_ptr;

	}
}
