#pragma once

#include "Action.h"

#include <string>

#include "World/Mesh/Chunk/Block/Block.h"

namespace action {


	struct RegisterBlockTypeAction final : public Action {
	public:
		RegisterBlockTypeAction( const world::mesh::chunk::block::Block& block ) : block_( block ) {}

		ActionType type() const override { return ActionType::RegisterBlockTypeAction; }

		world::mesh::chunk::block::Block block_;

	};


}