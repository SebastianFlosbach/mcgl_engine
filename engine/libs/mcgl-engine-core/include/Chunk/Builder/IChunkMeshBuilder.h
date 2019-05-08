#pragma once

#include <functional>

namespace coordinates {
struct ChunkCoordinates;
}

namespace mesh {
class Mesh;
}

class ChunkCollection;


namespace chunk {
namespace builder {

typedef std::function<void( const coordinates::ChunkCoordinates& position, mesh::Mesh* mesh )> CHUNK_MESH_BUILDER_CALLBACK;

class IChunkMeshBuilder {
public:
	IChunkMeshBuilder() = default;

	virtual void build( const coordinates::ChunkCoordinates& position, const ChunkCollection& chunks ) = 0;
	virtual void registerCallback( CHUNK_MESH_BUILDER_CALLBACK& callback ) = 0;
	virtual void deregisterCallback() = 0;


};


}
}
