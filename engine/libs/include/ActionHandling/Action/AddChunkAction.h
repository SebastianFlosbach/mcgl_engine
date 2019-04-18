#pragma once

#include "Action.h"

#include "../../World/Chunk/Chunk.h"


namespace action {


	struct AddChunkAction : public Action {
	public:
		AddChunkAction( const world::chunk::Chunk& chunk ) : chunk_( chunk ) {}

		ActionType type() const override { return ActionType::AddChunkAction; }

		world::chunk::Chunk chunk_;
	};


}