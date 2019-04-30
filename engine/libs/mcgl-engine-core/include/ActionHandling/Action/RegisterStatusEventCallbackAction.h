#pragma once

#include "Action.h"


namespace action {


	struct RegisterStatusEventCallbackAction final : public Action {
	public:
		RegisterStatusEventCallbackAction(MCGL_STATUS_EVENT_CALLBACK callback) : callback_(callback) {}

		ActionType type() const override { return ActionType::RegisterStatusEventCallbackAction; }

		MCGL_STATUS_EVENT_CALLBACK callback_;
	};


}