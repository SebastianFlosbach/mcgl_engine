#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetShaderAction : public Action {
public:
	SetShaderAction( Shader&& shader ) : shader_( std::move( shader ) ) {}

	ActionType type() const override { return ActionType::SetShaderAction; }

	Shader shader_;
};


}