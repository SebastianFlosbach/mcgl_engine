#pragma once

#include "Action.h"


namespace action {


	struct RotateCameraAction final : public Action {
	public:
		RotateCameraAction(const UNUM32 cameraId, const double pitch, const double yaw, const double roll) :
			cameraId_( cameraId ),
			pitch_( pitch ),
			yaw_( yaw ),
			roll_( roll ){

		}

		ActionType type() const override { return ActionType::RotateCameraAction; }

		UNUM32 cameraId_;
		double pitch_;
		double yaw_;
		double roll_;
	};


}