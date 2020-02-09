#include "Definition/mcgl_engine_def.h"

std::string to_string( MCGLShaderType type ) {
	switch( type ) {
		case MCGLShaderType::CUBE:
			return "CUBE";
		case MCGLShaderType::SKYBOX:
			return "SKYBOX";
		default:
			return "<UNKNOWN>";
	}
}
