#pragma once

#include "Logging/ILogger.h"
#include "Chunk/Block/BlockLibrary.h"
#include "Chunk/ChunkCollection.h"
#include "Chunk/Builder/IChunkMeshBuilder.h"
#include "World/World.h"
#include "Rendering/Renderer.h"


class AssetManager {
public:
	AssetManager( const ILogger& logger ) {
		pBlockLibrary_ = std::make_unique<chunk::block::BlockLibrary>();
		pChunkCollection_ = std::make_unique<chunk::ChunkCollection>();
		pWorld_ = std::make_unique<world::World>( logger );
		pRenderer_ = std::make_unique<Renderer>();
	}

	~AssetManager() = default;

	chunk::block::BlockLibrary* getBlockLibrary() const {
		return pBlockLibrary_.get();
	}

	chunk::ChunkCollection* getChunkCollection() const {
		return pChunkCollection_.get();
	}

	world::World* getWorld() const {
		return pWorld_.get();
	}

	void setChunkMeshBuilder( chunk::builder::IChunkMeshBuilder* pChunkMeshBuilder ) {
		pChunkMeshBuilder_ = std::unique_ptr<chunk::builder::IChunkMeshBuilder>( pChunkMeshBuilder );
	}

	chunk::builder::IChunkMeshBuilder* getChunkMeshBuilder() const {
		return pChunkMeshBuilder_.get();
	}

	Renderer* getRenderer() {
		return pRenderer_.get();
	}

private:
	Renderer_ptr							pRenderer_;
	chunk::block::BlockLibrary_ptr			pBlockLibrary_;
	chunk::ChunkCollection_ptr				pChunkCollection_;
	world::World_ptr						pWorld_;
	chunk::builder::IChunkMeshBuilder_ptr	pChunkMeshBuilder_;


};

typedef std::unique_ptr<AssetManager> AssetManager_ptr;
