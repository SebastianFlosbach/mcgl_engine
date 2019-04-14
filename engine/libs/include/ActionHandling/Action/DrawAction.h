#pragma once

#include "Action.h"


namespace action {


	struct DrawAction final : public Action {
	public:
		DrawAction() = default;

		ActionType type() const override { return ActionType::DrawAction; }

	};


}