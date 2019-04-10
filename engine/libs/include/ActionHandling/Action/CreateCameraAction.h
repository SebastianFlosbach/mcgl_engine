#pragma once

#include "Action.h"

typedef std::function<void(unsigned int)> ReturnCreateCameraAction;

namespace action {


	struct CreateCameraAction final : public Action {
	public:
		CreateCameraAction(const double x, const double y, const double z, const double pitch, const double yaw, const double roll, ReturnCreateCameraAction returnCallback) :
			x_(x),
			y_(y),
			z_(z),
			pitch_(pitch),
			yaw_(yaw),
			roll_(roll),
			returnCallback_( returnCallback ){
		}

		ActionType type() const override { return ActionType::CreateCameraAction; }

		double x_;
		double y_;
		double z_;
		double pitch_;
		double yaw_;
		double roll_;
		ReturnCreateCameraAction returnCallback_;
	};


}