#pragma once

#include "Action.h"

#include <string>


namespace action {


	struct SetTexturesAction : public Action {
	public:
		SetTexturesAction( const std::string& texturePath, const int size, const int textureCount ) : texturePath_( texturePath ), size_( size ), textureCount_( textureCount ) {}

		ActionType type() const override { return ActionType::SetTexturesAction; }

		std::string texturePath_;
		int size_;
		int textureCount_;
	};


}