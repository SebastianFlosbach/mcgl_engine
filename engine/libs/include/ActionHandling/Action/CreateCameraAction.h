#pragma once

#include "Action.h"


namespace action {


	struct CreateCameraAction final : public Action {
	public:
		CreateCameraAction() = default;

		ActionType type() const override { return ActionType::CreateCameraAction; }

	};


}