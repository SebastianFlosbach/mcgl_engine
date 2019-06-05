#pragma once

#include "Action.h"


namespace action {


struct DestroyAction : public Action {
public:
	DestroyAction() = default;

	ActionType type() const override { return ActionType::DestroyAction; }

};


}
