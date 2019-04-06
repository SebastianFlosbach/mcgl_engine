#pragma once

#include "../Action.h"

namespace action {


struct CreateEngine final : public Action {
public:	
	ActionType getType() const override { return ActionType::CreateEngine; }

};


}