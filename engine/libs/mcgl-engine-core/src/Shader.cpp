#include "Shader.h"

#include <iostream>

const char* to_string( const GLenum type ) {
	switch ( type ) {
		case GL_VERTEX_SHADER:
			return "VERTEX";
		case GL_FRAGMENT_SHADER:
			return "FRAGMENT";
		default:
			return "<UNKNOWN>";
	}
}

namespace std {
	std::string to_string( ShaderType type ) {
		switch( type )
		{
		case ShaderType::Chunk:
			return "Chunk";
		case ShaderType::Skybox:
			return "Skybox";
		default:
			return "<invalid>";
		}
	}
}

Shader::Shader() {
	hShaderProgramm_ = glCreateProgram();
}

// Move constructor
Shader::Shader( Shader&& other ) noexcept {
	*this = std::move( other );
}

Shader& Shader::operator=( Shader&& other ) noexcept {
	hShaderProgramm_ = other.hShaderProgramm_;
	other.hShaderProgramm_ = 0;

	return *this;
}

// Destructor
Shader::~Shader() {
	if ( hShaderProgramm_ != 0 ) {
		glDeleteProgram( hShaderProgramm_ );
	}
}

void Shader::addVertexShader( const std::string& path ) {
	addShader( path, GL_VERTEX_SHADER );
}

void Shader::addFragmentShader( const std::string& path ) {
	addShader( path, GL_FRAGMENT_SHADER );
}

void Shader::addShader( const std::string& path, GLenum type ) {
	std::ifstream file( path );
	if ( !file.is_open() ) {
		throw std::runtime_error( std::string( "Shader::addShader(): Cannot open shader file at " ) + path );
	}

	std::string shaderSource = std::string( std::istreambuf_iterator<char>( file ), std::istreambuf_iterator<char>() );
	const char* c_shaderSource = shaderSource.c_str();

	int success;
	char infoLog[512];

	auto hShader = glCreateShader( type );
	glShaderSource( hShader, 1, &c_shaderSource, nullptr );
	glCompileShader( hShader );
	glGetShaderiv( hShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( hShader, 512, nullptr, infoLog );
		std::cout << "ERROR::SHADER::" << to_string( type ) << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		return;
	}

	glAttachShader( hShaderProgramm_, hShader );
	glDeleteShader( hShader );
}

void Shader::compile() {
	int success;
	char infoLog[512];

	glLinkProgram( hShaderProgramm_ );
	glGetProgramiv( hShaderProgramm_, GL_LINK_STATUS, &success );
	if ( !success ) {
		glGetProgramInfoLog( hShaderProgramm_, 512, nullptr, infoLog );
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return;
	}
}