#pragma once

#include "../Action.h"

#include <string>

namespace action {


struct CreateWindow final : public Action {
public:
	CreateWindow( unsigned int width, unsigned int height, const std::string title ) : width_( width ), height_( height ), title_( std::move( title ) ) {}

	ActionType getType() const override { return ActionType::CreateWindow; }

	unsigned int width_;
	unsigned int height_;
	std::string title_;
};


}