#pragma once

#include "Action.h"

#include "Chunk/Chunk.h"


namespace action {


	struct AddChunkAction : public Action {
	public:
		AddChunkAction( chunk::Chunk_ptr&& chunk ) : pChunk_( std::move( chunk ) ) {}

		ActionType type() const override { return ActionType::AddChunkAction; }

		chunk::Chunk_ptr pChunk_;
	};


}