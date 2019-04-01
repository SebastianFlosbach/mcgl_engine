#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "Chunk/Chunk.h"
#include "Chunk/ChunkMeshBuilder.h"
#include "Block/BlockLibrary.h"
#include "Texture/TextureAtlas.h"
#include "Mesh/Mesh.h"
#include "Shader.h"

namespace world {
struct ChunkPosition {
	const int x;
	const int z;
};
}

namespace std {

template<>
struct hash<world::ChunkPosition> {
	size_t operator()( const world::ChunkPosition& chunkPosition ) const noexcept {
		int x, z;

		if ( chunkPosition.x >= 0 ) {
			x = chunkPosition.x * 2;
		} else {
			x = -chunkPosition.x * 2 - 1;
		}

		if ( chunkPosition.z >= 0 ) {
			z = chunkPosition.z * 2;
		} else {
			z = -chunkPosition.z * 2 - 1;
		}

		return ((x + z) * (x + z + 1) / 2) * z;
	}
};

template<>
struct equal_to<world::ChunkPosition> {
	constexpr bool operator()( const world::ChunkPosition& left, const world::ChunkPosition& right ) const {	// apply operator== to operands
		return left.x == right.x && left.z == right.z;
	}
};

}

namespace world {

class World {
public:
	World() = default;

	World( const World& other ) = delete;
	World& operator=( const World& other ) = delete;

	World( World&& other ) = delete;
	World& operator=( World&& other ) = delete;

	void addChunk( const int x, const int z, const chunk::Chunk& chunk ) {
		chunks_.insert( { { x, z }, chunk } );
	}

	void removeChunk( const int x, const int z ) {
		chunks_.erase( { x, z } );
	}

	std::vector<std::unique_ptr<Mesh>> generateMesh( const block::BlockLibrary& blockLibrary, const texture::TextureAtlas& textureAtlas ) {
		chunk::ChunkMeshBuilder meshBuilder( blockLibrary );
		std::vector<std::unique_ptr<Mesh>> mesh( chunks_.size() );

		int i = 0;
		for ( auto& chunk : chunks_ ) {
			mesh[i++] = std::make_unique<Mesh>( meshBuilder.createChunkMesh( chunk.second, textureAtlas ) );
		}

		return mesh;
	}

private:
	std::unordered_map<ChunkPosition, chunk::Chunk> chunks_;

};


}