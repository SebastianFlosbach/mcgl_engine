#pragma once

#include "Action.h"

#include <string>


namespace action {


struct SetTextureAction : public Action {
public:
	SetTextureAction( MCGLTextureType type, const std::string& name, const std::string& path, UNUM32 textureSize = 0, UNUM32 textureCount = 0 ) : 
		type_( type ), name_( name ), path_( path ), textureSize_( textureSize ), textureCount_( textureCount ) {}

	ActionType type() const override { return ActionType::SetTextureAction; }

	MCGLTextureType type_;
	std::string name_;
	std::string path_;
	UNUM32 textureSize_;
	UNUM32 textureCount_;

};


}
