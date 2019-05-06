#pragma once

#include <functional>


namespace world {
namespace chunk {
namespace builder {

typedef std::function<void( const coordinates::ChunkCoordinates& position, mesh::Mesh* mesh )> CHUNK_MESH_BUILDER_CALLBACK;

class IChunkMeshBuilder {
public:
	IChunkMeshBuilder() = delete;

	virtual void build( const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks ) = 0;
	virtual void registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) = 0;


};


}
}
}

