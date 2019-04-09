#pragma once

#include "Action.h"

#include <string>

#include "../../World/Chunk/Chunk.h"


namespace action {


	struct AddChunkAction : public Action {
	public:
		AddChunkAction(const int x, const int z, const world::chunk::Chunk& chunk) : x_(x), z_(z), chunk_( chunk ) {}

		ActionType type() const override { return ActionType::AddChunkAction; }

		int x_;
		int z_;
		world::chunk::Chunk chunk_;
	};


}