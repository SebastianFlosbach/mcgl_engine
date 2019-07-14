#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetTextureAction : public Action {
public:
	SetTextureAction( MCGLTextureType type, const std::string& path ) : type_( type ), path_( path ) {}

	ActionType type() const override { return ActionType::SetTextureAction; }

	MCGLTextureType type_;
	std::string path_;

};


}
