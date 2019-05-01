#pragma once

#include <future>
#include <ctpl_stl.h>

#include "Mesh/Mesh.h"
#include "Chunk/Builder/ChunkMeshBuilder.h"
#include "Chunk/ChunkCollection.h"
#include "Coordinates/ChunkCoordinates.h"

namespace chunk {
namespace builder {


/**
	Callback to return created meshes
	\param position Position of the chunk the mesh was build from
	\param mesh Pointer to the generated mesh
*/
typedef std::function<void( const coordinates::ChunkCoordinates& position, mesh::Mesh* mesh )> CHUNK_MESH_BUILDER_CALLBACK;

/**
	Class to create meshes from chunks asynchronously
	\see ChunkMeshBuilder
*/
class ThreadedChunkMeshBuilder : private ChunkMeshBuilder {
public:

	ThreadedChunkMeshBuilder() = default;

	/**
		Create ThreadedChunkMeshBuilder.
		\param blockLibrary BlockLibrary for interpreting chunk data
		\param textureAtlas TextureAtlas to use for the mesh
		\param threadCount Number of threads the builder is allowed to use
	*/
	ThreadedChunkMeshBuilder( const block::BlockLibrary_sptr& blockLibrary, const texture::TextureAtlas_sptr& textureAtlas, const unsigned int threadCount );

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
		\param callback Callback that returns the generated mesh. \see CHUNK_MESH_BUILDER_CALLBACK
		\return Mesh pointer or nullptr if chunk does not exist
	*/
	void build( const coordinates::ChunkCoordinates& position, const ChunkCollection& world );

	/**
		Register callback that is called whenever a mesh is build
		\param callback Callback to register
	*/
	void registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback );

	/**
		Deregister the mesh callback.
		All further meshes are lost.
	*/
	void deregisterCallback();

private:
	ctpl::thread_pool threadPool_;

	CHUNK_MESH_BUILDER_CALLBACK callback_;

};

typedef std::unique_ptr<ThreadedChunkMeshBuilder> ThreadedChunkMeshBuilder_ptr;


}
}
