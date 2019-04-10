#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetShaderAction : public Action {
public:
	SetShaderAction( const std::string& vertexPath, const std::string& fragmentPath ) : vertexPath_( vertexPath ), fragmentPath_( fragmentPath ) {}

	ActionType type() const override { return ActionType::SetShaderAction; }

	std::string vertexPath_;
	std::string fragmentPath_;
};


}