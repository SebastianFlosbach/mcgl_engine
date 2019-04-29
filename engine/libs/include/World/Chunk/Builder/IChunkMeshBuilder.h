#pragma once

#include "Mesh/Mesh.h"
#include "World/Chunk/ChunkCollection.h"
#include "Definition/mcgl_engine_def.h"

namespace world {
namespace chunk {
namespace builder {


class IChunkMeshBuilder {
public:
	virtual mesh::Mesh* build( const ChunkCoordinates& position, const ChunkCollection& world ) const = 0;

};

typedef std::unique_ptr<IChunkMeshBuilder> IChunkMeshBuilder_ptr;


}
}
}