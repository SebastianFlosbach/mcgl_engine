#pragma once

#include "Action.h"

#include <string>


namespace action {


	struct SetTexturesAction : public Action {
	public:
		SetTexturesAction(const char* path, const unsigned int textureSize, const unsigned int textureCount) : path_( path ), textureSize_( textureSize ), textureCount_( textureCount ) {}

		ActionType type() const override { return ActionType::SetTexturesAction; }

		const char* path_;
		unsigned int textureSize_;
		unsigned int textureCount_;
	};


}