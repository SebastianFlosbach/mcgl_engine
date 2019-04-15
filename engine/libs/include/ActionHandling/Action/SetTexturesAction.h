#pragma once

#include "Action.h"

#include <string>


namespace action {


	struct SetTexturesAction : public Action {
	public:
		SetTexturesAction( const char* texturePath, const int size, const int textureCount ) : texturePath_( texturePath ), size_( size ), textureCount_( textureCount ) {}

		ActionType type() const override { return ActionType::SetTexturesAction; }

		const char* texturePath_;
		int size_;
		int textureCount_;
	};


}