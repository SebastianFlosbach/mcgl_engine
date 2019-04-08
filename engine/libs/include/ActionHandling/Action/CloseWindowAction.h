#pragma once

#include "Action.h"

#include <string>

namespace action {


struct CloseWindowAction final : public Action {
public:
	CloseWindowAction() = default;

	ActionType type() const override { return ActionType::CloseWindowAction; }

};


}