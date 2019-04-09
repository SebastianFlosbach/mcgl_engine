#pragma once

#include "Action.h"

#include <string>


namespace action {


	struct RunAction : public Action {
	public:
		RunAction() = default;

		ActionType type() const override { return ActionType::RunAction; }

	};


}