#pragma once

#include "Action.h"


namespace action {


	struct RotateCameraAction final : public Action {
	public:
		RotateCameraAction( const double pitch, const double yaw, const double roll) :
			pitch_( pitch ),
			yaw_( yaw ),
			roll_( roll ){

		}

		ActionType type() const override { return ActionType::RotateCameraAction; }

		double pitch_;
		double yaw_;
		double roll_;
	};


}