#pragma once

#include "Action.h"

#include <string>

namespace action {


struct CreateWindowAction final : public Action {
public:
	CreateWindowAction( unsigned int width, unsigned int height, const std::string& title ) : width_( width ), height_( height ), title_( title ) {}

	ActionType type() const override { return ActionType::CreateWindowAction; }

	unsigned int width_;
	unsigned int height_;
	std::string title_;
};


}