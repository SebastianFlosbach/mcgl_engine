#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetSkyboxShaderAction : public Action {
public:
	SetSkyboxShaderAction( const std::string& vertexShaderPath, const std::string& fragmentShaderPath ) : vertexShaderPath_( vertexShaderPath ), fragmentShaderPath_( fragmentShaderPath ) {}

	ActionType type() const override { return ActionType::SetSkyboxShaderAction; }

	std::string vertexShaderPath_{};
	std::string fragmentShaderPath_{};
};


}