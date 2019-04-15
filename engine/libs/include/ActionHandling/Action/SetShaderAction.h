#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetShaderAction : public Action {
public:
	SetShaderAction( const char* vertexShaderPath, const char* fragmentShaderPath ) : vertexShaderPath_( vertexShaderPath ), fragmentShaderPath_( fragmentShaderPath ) {}

	ActionType type() const override { return ActionType::SetShaderAction; }

	const char* vertexShaderPath_{ nullptr };
	const char* fragmentShaderPath_{ nullptr };
};


}