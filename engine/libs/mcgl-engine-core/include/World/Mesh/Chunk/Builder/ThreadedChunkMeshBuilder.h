#pragma once

#include <future>
#include <ctpl_stl.h>

#include "Chunk/Builder/ChunkMeshBuilder.h"
#include "Chunk/ChunkCollection.h"
#include "Coordinates/ChunkCoordinates.h"
#include "Logging/ILogger.h"


namespace world {
namespace mesh {
namespace chunk {
namespace builder {


/**
	Class to create meshes from chunks asynchronously
	\see ChunkMeshBuilder
*/
class ThreadedChunkMeshBuilder : public ChunkMeshBuilder {
public:

	ThreadedChunkMeshBuilder( const logging::ILogger& logger, UNUM32 threadCount );

	/**
		Create ThreadedChunkMeshBuilder.
		\param blockLibrary BlockLibrary for interpreting chunk data
		\param textureAtlas TextureAtlas to use for the mesh
		\param threadCount Number of threads the builder is allowed to use
	*/
	ThreadedChunkMeshBuilder( const logging::ILogger& logger, const block::BlockLibrary* blockLibrary, const texture::TextureAtlas_sptr& textureAtlas, UNUM32 threadCount );

	/**

	*/
	void setBlockLibrary( const block::BlockLibrary* blockLibrary );

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
	void build( const coordinates::ChunkCoordinates& position, const ChunkCollection& world ) override;

	/**
		Register callback that is called whenever a mesh is build
		\param callback Callback to register
	*/
	void registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) override;

	/**
		Deregister the mesh callback.
		All further meshes are lost.
	*/
	void deregisterCallback() override;

private:
	ctpl::thread_pool threadPool_;

};

typedef std::unique_ptr<ThreadedChunkMeshBuilder> ThreadedChunkMeshBuilder_ptr;


}
}
}
}
