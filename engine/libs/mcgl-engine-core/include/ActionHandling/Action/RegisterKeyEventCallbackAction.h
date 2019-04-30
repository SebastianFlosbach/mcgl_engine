#pragma once

#include "Action.h"


namespace action {


	struct RegisterKeyEventCallbackAction final : public Action {
	public:
		RegisterKeyEventCallbackAction(MCGL_KEY_EVENT_CALLBACK callback) : callback_( callback ) {}

		ActionType type() const override { return ActionType::RegisterKeyEventCallbackAction; }

		MCGL_KEY_EVENT_CALLBACK callback_;
	};


}