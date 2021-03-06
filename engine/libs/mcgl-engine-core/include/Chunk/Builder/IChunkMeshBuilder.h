#pragma once

#include <functional>
#include <memory>

#include "Chunk/Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "Coordinates/ChunkCoordinates.h"
#include "Chunk/ChunkCollection.h"
#include "Mesh/Mesh.h"


namespace chunk {
namespace builder {

/**
	Callback to return created meshes
	\param position Position of the chunk the mesh was build from
	\param mesh Pointer to the generated mesh
*/
typedef std::function<void( const coordinates::ChunkCoordinates& position, mesh::Mesh* mesh )> CHUNK_MESH_BUILDER_CALLBACK;

class IChunkMeshBuilder {
public:
	IChunkMeshBuilder() = default;
	virtual ~IChunkMeshBuilder() = default;

	virtual void setBlockLibrary( const block::BlockLibrary* blockLibrary ) = 0;
	virtual void setTextureAtlas( const texture::TextureAtlas_sptr& textureAtlas ) = 0;

	virtual void build( const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks ) = 0;

	virtual void registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) = 0;
	virtual void deregisterCallback() = 0;

};

typedef std::unique_ptr<IChunkMeshBuilder> IChunkMeshBuilder_ptr;


}
}
