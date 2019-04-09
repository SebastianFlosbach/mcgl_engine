#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetShaderData : public Action {
public:
	SetShaderData( const std::string& vertexPath, const std::string& fragmentPath ) : vertexPath_( vertexPath ), fragmentPath_( fragmentPath ) {}

	ActionType type() const override { return ActionType::SetShaderAction; }

	std::string vertexPath_;
	std::string fragmentPath_;
};


}