#pragma once

#include "Action.h"

#include <string>


namespace action {


	struct SetTexturesAction : public Action {
	public:
		SetTexturesAction( texture::TextureAtlas&& textureAtlas ) : textureAtlas_( std::move( textureAtlas ) ) {}

		ActionType type() const override { return ActionType::SetTexturesAction; }

		texture::TextureAtlas textureAtlas_;
	};


}