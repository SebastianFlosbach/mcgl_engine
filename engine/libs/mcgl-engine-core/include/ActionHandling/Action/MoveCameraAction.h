#pragma once

#include "Action.h"


namespace action {


	struct MoveCameraAction final : public Action {
	public:
		MoveCameraAction( double dx, double dy, double dz) : 
			dx_( dx ),
			dy_( dy ),
			dz_( dz ) {
		}

		ActionType type() const override { return ActionType::MoveCameraAction; }

		double dx_;
		double dy_;
		double dz_;
	};


}