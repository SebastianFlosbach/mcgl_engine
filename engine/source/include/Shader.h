#pragma once
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
	// Default constructor
	Shader();

	// Copy constructor
	Shader( const Shader& other ) = delete;
	Shader& operator=( const Shader& other ) = delete;

	// Move constructor
	Shader( Shader&& other ) noexcept;
	Shader& operator=( Shader&& other ) noexcept;

	// Destructor
	~Shader();

	unsigned int id() const {
		return hShaderProgramm_;
	}

	void addVertexShader( const std::string& path );
	void addFragmentShader( const std::string& path );

	void compile();

	void use() {
		glUseProgram( hShaderProgramm_ );
	}

	inline int getUniform( const char* uniform ) {
		return glGetUniformLocation( hShaderProgramm_, uniform );
	}

	void setUniformInt( const char* uniform, int value ) {
		glUniform1i( getUniform( uniform ), value );
	}

	void setUniformMat4f( const char* uniform, const glm::mat4& matrix ) {
		glUniformMatrix4fv( getUniform( uniform ), 1, GL_FALSE, glm::value_ptr( matrix ) );
	}

private:
	unsigned int hShaderProgramm_;

	inline void addShader( const std::string& path, GLenum type );

};