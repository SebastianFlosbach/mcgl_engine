#pragma once

#include <vector>
#include <memory>

#include "Chunk/Chunk.h"
#include "Chunk/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "Mesh/Mesh.h"
#include "Chunk/ChunkCollection.h"


namespace world {
class World;
}

namespace chunk {
namespace builder {


/**
	Class to create meshes from chunks
*/
class ChunkMeshBuilder {
public:

	ChunkMeshBuilder() = default;

	/**
		Create a ChunkMeshBuilder that uses a specific block library and texture atlas
		\param blockLibrary BlockLibrary for interpreting chunk data
		\param textureAtlas TextureAtlas to use for the mesh
	*/
	ChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas );

	/**

	*/
	void setBlockLibrary( const block::BlockLibrary_sptr& blockLibrary );

	/**

	*/
	void setTextureAtlas( const texture::TextureAtlas_sptr& textureAtlas );

	/**
		Create the mesh for chunk at a position in the world
		\param position Position of the chunk
		\param world World the chunk is in
		\return Mesh pointer or nullptr if chunk does not exist
	*/
	mesh::Mesh* build( const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks );

private:
	block::BlockLibrary_sptr pBlockLibrary_;
	texture::TextureAtlas_sptr pTextureAtlas_; 

	inline void addIndices( std::vector<UNUM32>& indices, UNUM32& indexBase );

	// current block position, current chunk position, chunks, current chunk, id of current block
	inline void left	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void right	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void top		( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void bottom	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void front	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void back	( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<Vertex>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );

};

typedef std::unique_ptr<ChunkMeshBuilder> ChunkMeshBuilder_ptr;

}
}
