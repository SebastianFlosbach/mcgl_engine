#pragma once

#include <vector>
#include <memory>

#include "World/Chunk/Chunk.h"
#include "World/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "Mesh/Mesh.h"
#include "World/Chunk/ChunkCollection.h"


namespace world {
class World;

namespace chunk {
namespace builder {


/**
	Class to create meshes from chunks
*/
class ChunkMeshBuilder {
public:

	/**
		Create a ChunkMeshBuilder that uses a specific block library and texture atlas
		\param blockLibrary BlockLibrary for interpreting chunk data
		\param textureAtlas TextureAtlas to use for the mesh
	*/
	ChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas );

	/**
		Create the mesh for chunk at a position in the world
		\param position Position of the chunk
		\param world World the chunk is in
		\return Mesh pointer or nullptr if chunk does not exist
	*/
	mesh::Mesh* build( const ChunkCoordinates& position, const ChunkCollection& chunks );

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
}
