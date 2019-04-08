#pragma once

#include "Action.h"
#include "ActionData.h"

#include <string>

namespace action {


struct CreateWindowData final : public ActionData {
public:
	CreateWindowData( unsigned int width, unsigned int height, const std::string& title ) : width_( width ), height_( height ), title_( title ) {}

	ActionType type() const override { return ActionType::CreateWindowAction; }

	unsigned int width_;
	unsigned int height_;
	std::string title_;
};


}