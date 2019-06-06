#pragma once

#include <fstream>
#include <map>
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Definition/mcgl_engine_def.h"


enum class ShaderType {
	Chunk,
	Skybox
};

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

class Shader {
public:
	// Default constructor
	Shader();

	~Shader();

	// Copy constructor
	Shader( const Shader& other ) = delete;
	Shader& operator=( const Shader& other ) = delete;

	// Move constructor
	Shader( Shader&& other ) noexcept;
	Shader& operator=( Shader&& other ) noexcept;


	unsigned int id() const {
		return hShaderProgramm_;
	}

	void addVertexShader( const std::string& path );
	void addFragmentShader( const std::string& path );

	void compile();

	void use() {
		glUseProgram( hShaderProgramm_ );
	}

	inline NUM32 getUniform( const char* uniform ) {
		
		auto it = uniforms_.find( uniform );

		if( it != uniforms_.end() ) {
			return it->second;
		}

		NUM32 uniformLocation = glGetUniformLocation( hShaderProgramm_, uniform );
		uniforms_.emplace( std::string( uniform ), uniformLocation );

		return uniformLocation;
	}

	void setUniformInt( const char* uniform, NUM32 value ) {
		glUniform1i( getUniform( uniform ), value );
	}

	void setUniformMat4f( const char* uniform, const glm::mat4& matrix ) {
		glUniformMatrix4fv( getUniform( uniform ), 1, GL_FALSE, glm::value_ptr( matrix ) );
	}

private:
	UNUM32 hShaderProgramm_;

	std::map<std::string, NUM32> uniforms_;

	inline void addShader( const std::string& path, GLenum type );

};

typedef std::unique_ptr<Shader> Shader_ptr;
