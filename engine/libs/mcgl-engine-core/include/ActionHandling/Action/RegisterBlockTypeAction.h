#pragma once

#include "Action.h"

#include <string>

#include "Chunk/Block/Block.h"

namespace action {


	struct RegisterBlockTypeAction final : public Action {
	public:
		RegisterBlockTypeAction( const chunk::block::Block& block ) : block_( block ) {}

		ActionType type() const override { return ActionType::RegisterBlockTypeAction; }

		chunk::block::Block block_;

	};


}