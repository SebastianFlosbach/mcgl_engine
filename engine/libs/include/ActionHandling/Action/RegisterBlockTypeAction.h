#pragma once

#include "Action.h"

#include <string>

#include "../../World/Block/Block.h"

namespace action {


	struct RegisterBlockTypeAction final : public Action {
	public:
		RegisterBlockTypeAction( const world::block::Block& block, int id ) : block_( block ), id_( id ) {}

		ActionType type() const override { return ActionType::CloseWindowAction; }

		world::block::Block block_;
		int id_;
	};


}