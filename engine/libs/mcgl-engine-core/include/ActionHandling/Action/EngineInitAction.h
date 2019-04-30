#pragma once

#include "Action.h"

namespace action {


	struct EngineInitAction final : public Action {
	public:
		EngineInitAction() = default;

		ActionType type() const override { return ActionType::EngineInitAction; }

	};


}