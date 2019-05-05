#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetShaderAction : public Action {
public:
	SetShaderAction( const std::string& vertexShaderPath, const std::string& fragmentShaderPath ) : vertexShaderPath_( vertexShaderPath ), fragmentShaderPath_( fragmentShaderPath ) {}

	ActionType type() const override { return ActionType::SetShaderAction; }

	std::string vertexShaderPath_{};
	std::string fragmentShaderPath_{};
};


}