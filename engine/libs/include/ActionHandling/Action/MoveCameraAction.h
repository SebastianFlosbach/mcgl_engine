#pragma once

#include "Action.h"


namespace action {


	struct MoveCameraAction final : public Action {
	public:
		MoveCameraAction(unsigned int cameraId, double dx, double dy, double dz) : 
			cameraId_( cameraId ),
			dx_( dx ),
			dy_( dy ),
			dz_( dz ) {
		}

		ActionType type() const override { return ActionType::MoveCameraAction; }

		unsigned int cameraId_;
		double dx_;
		double dy_;
		double dz_;
	};


}