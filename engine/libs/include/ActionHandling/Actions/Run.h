#pragma once

#include "../Action.h"

namespace action {


struct Run final : public Action {
public:
	ActionType getType() const override { return ActionType::Run; }
};


}