#pragma once

#include "Action.h"

#include <string>


namespace action {


	struct StopAction : public Action {
	public:
		StopAction() = default;

		ActionType type() const override { return ActionType::StopAction; }

	};


}