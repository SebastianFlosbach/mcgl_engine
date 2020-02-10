#pragma once

#include "World/Mesh/Chunk/Builder/IChunkMeshBuilder.h"

#include <vector>
#include <memory>

#include "World/Mesh/Chunk/Chunk.h"
#include "Logging/ILogger.h"
#include "Texture/TextureLibrary.h"


namespace world {
class World;

namespace mesh {
namespace chunk {
namespace builder {


/**
	Class to create meshes from chunks
*/
class ChunkMeshBuilder : public IChunkMeshBuilder {
public:
	ChunkMeshBuilder( const logging::ILogger& logger );

	/**
		Create a ChunkMeshBuilder that uses a specific block library and texture atlas
		\param blockLibrary BlockLibrary for interpreting chunk data
		\param textureAtlas TextureAtlas to use for the mesh
	*/
	ChunkMeshBuilder( const logging::ILogger& logger, const block::BlockLibrary* blockLibrary, texture::TextureLibrary* textureLibrary );

	/**

	*/
	virtual void setBlockLibrary( const block::BlockLibrary* blockLibrary ) override;

	/**

	*/
	virtual void setTextureLibrary( texture::TextureLibrary* textureLibrary ) override;

	/**
		Create the mesh for chunk at a position in the world
		\param position Position of the chunk
		\param world World the chunk is in
		\return Mesh pointer or nullptr if chunk does not exist
	*/
	virtual void build( const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks ) override;

	virtual void registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) override;
	virtual void deregisterCallback() override;

protected:
	const logging::ILogger& logger_;

private:
	const block::BlockLibrary* pBlockLibrary_;
	texture::TextureLibrary* pTextureLibrary_;

	texture::TextureAtlas* pTextureAtlas_;

	CHUNK_MESH_BUILDER_CALLBACK callback_;

	inline void addIndices( std::vector<UNUM32>& indices, UNUM32& indexBase );

	inline void left( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<VertexCT>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void right( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<VertexCT>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void top( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<VertexCT>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void bottom( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<VertexCT>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void front( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<VertexCT>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );
	inline void back( NUM32 x, NUM32 y, NUM32 z, const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks, const Chunk& chunk, UNUM32 blockId, std::vector<VertexCT>& vertices, std::vector<UNUM32>& indices, UNUM32& indexBase );

};

typedef std::unique_ptr<ChunkMeshBuilder> ChunkMeshBuilder_ptr;


}
}
}
}
