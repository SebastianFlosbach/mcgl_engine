#pragma once

#include "Logging/ILogger.h"
#include "World/Mesh/Chunk/Block/BlockLibrary.h"
#include "World/Mesh/Chunk/ChunkCollection.h"
#include "World/Mesh/Chunk/Builder/IChunkMeshBuilder.h"
#include "World/World.h"
#include "Rendering/Renderer.h"


class AssetManager {
public:
	AssetManager( const logging::ILogger& logger ) {
		pBlockLibrary_ = std::make_unique<world::mesh::chunk::block::BlockLibrary>();
	}

	~AssetManager() = default;

	world::mesh::chunk::block::BlockLibrary* getBlockLibrary() const {
		return pBlockLibrary_.get();
	}

private:
	std::vector<texture::Texture> textures_;
	world::mesh::chunk::block::BlockLibrary_ptr	pBlockLibrary_;

};

typedef std::unique_ptr<AssetManager> AssetManager_ptr;
