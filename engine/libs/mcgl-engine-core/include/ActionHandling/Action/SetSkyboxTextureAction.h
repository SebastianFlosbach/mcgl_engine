#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetSkyboxTextureAction : public Action {
public:
	SetSkyboxTextureAction( 
		const std::string& right,
		const std::string& left,
		const std::string& top,
		const std::string& bottom,
		const std::string& front,
		const std::string& back ) : 
		right_( right ),
		left_( left ),
		top_( top ),
		bottom_( bottom ),
		front_( front ),
		back_( back )
	{}

	ActionType type() const override { return ActionType::SetSkyboxTexturesAction; }

	const std::string right_;
	const std::string left_;
	const std::string top_;
	const std::string bottom_;
	const std::string front_;
	const std::string back_;

};


}