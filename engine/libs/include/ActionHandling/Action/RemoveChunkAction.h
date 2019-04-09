#pragma once

#include "Action.h"

#include <string>


namespace action {


	struct RemoveChunkAction : public Action {
	public:
		RemoveChunkAction( const int x, const int z) : x_( x ), z_( z ) {}

		ActionType type() const override { return ActionType::RemoveChunkAction; }

		int x_;
		int z_;
	};


}