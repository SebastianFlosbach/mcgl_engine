#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetShaderAction : public Action {
public:
	SetShaderAction( MCGLShaderType type, const std::string& path ) : type_( type ), path_( path ) {
	}

	ActionType type() const override { return ActionType::SetShaderAction; }

	MCGLShaderType type_;
	std::string path_;

};


}
