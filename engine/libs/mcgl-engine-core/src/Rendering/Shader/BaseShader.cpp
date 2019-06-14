#include "Rendering/Shader/BaseShader.h"


namespace rendering {
namespace shader {


BaseShader::BaseShader() {
	id_ = glCreateProgram();
}

BaseShader::~BaseShader() {
	glDeleteProgram( id_ );
}

BaseShader::BaseShader( BaseShader&& other ) noexcept {
	id_ = other.id_;
	other.id_ = 0;
}

BaseShader& BaseShader::operator=( BaseShader&& other ) noexcept {
	if( &other == this ) {
		return other;
	}

	return std::move( other );
}

GLenum to_glEnum( ShaderType type ) {
	switch( type )
	{
	case rendering::shader::ShaderType::Vertex:
		return GL_VERTEX_SHADER;
	case rendering::shader::ShaderType::Fragment:
		return GL_FRAGMENT_SHADER;
	default:
		throw std::invalid_argument( "" );
	}
}

std::string to_string( ShaderType type ) {
	switch( type )
	{
	case rendering::shader::ShaderType::Vertex:
		return "Vertex";
	case rendering::shader::ShaderType::Fragment:
		return "Fragment";
	default:
		throw std::invalid_argument( "" );
	}
}


}
}
