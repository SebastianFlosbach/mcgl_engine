#pragma once

#include "Action.h"


namespace action {


	struct RegisterMouseEventCallbackAction final : public Action {
	public:
		RegisterMouseEventCallbackAction(MCGL_MOUSE_EVENT_CALLBACK callback) : callback_(callback) {}

		ActionType type() const override { return ActionType::RegisterMouseEventCallbackAction; }

		MCGL_MOUSE_EVENT_CALLBACK callback_;
	};


}