#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetShaderAction : public Action {
public:
	SetShaderAction( MCGLShaderType type, const std::string& vertexShaderPath, const std::string& fragmentShaderPath ) : type_( type ), vertexShaderPath_( vertexShaderPath ), fragmentShaderPath_( fragmentShaderPath ) {
	}

	ActionType type() const override { return ActionType::SetShaderAction; }

	MCGLShaderType type_;
	std::string vertexShaderPath_{};
	std::string fragmentShaderPath_{};

};


}
