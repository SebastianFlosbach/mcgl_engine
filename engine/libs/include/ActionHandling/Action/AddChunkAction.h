#pragma once

#include "Action.h"

#include "../../World/Chunk/Chunk.h"


namespace action {


	struct AddChunkAction : public Action {
	public:
		AddChunkAction( world::chunk::Chunk_ptr&& chunk ) : pChunk_( std::move( chunk ) ) {}

		ActionType type() const override { return ActionType::AddChunkAction; }

		world::chunk::Chunk_ptr pChunk_;
	};


}