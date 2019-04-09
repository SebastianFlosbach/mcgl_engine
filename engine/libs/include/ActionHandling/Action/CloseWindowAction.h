#pragma once

#include "Action.h"


namespace action {


struct CloseWindowAction final : public Action {
public:
	CloseWindowAction() = default;

	ActionType type() const override { return ActionType::CloseWindowAction; }

};


}