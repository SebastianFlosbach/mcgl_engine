#pragma once

#include "IShader.h"

#include <stdexcept>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>


namespace rendering{
namespace shader {


class BaseShader: public IShader {
public:
	BaseShader();
	virtual ~BaseShader();

	BaseShader( const BaseShader& other ) = delete;
	BaseShader& operator=( const BaseShader& other ) = delete;

	BaseShader( BaseShader&& other ) noexcept;
	BaseShader& operator=( BaseShader&& other ) noexcept;

	virtual UNUM32 id() const override {
		return id_;
	}

	virtual Type type() const = 0;

	virtual void addShader( const std::string& path, ShaderType type ) = 0;

	virtual void compile() = 0;

	virtual void use() override {
		glUseProgram( id_ );
	}

	virtual void setUniformInt( const char* uniform, NUM32 value ) override {
		glUseProgram( id_ );
		glUniform1i( getUniform( uniform ), value );
	}

	void setUniformMat4f( const char* uniform, const glm::mat4& matrix ) override {
		glUseProgram( id_ );
		glUniformMatrix4fv( getUniform( uniform ), 1, GL_FALSE, glm::value_ptr( matrix ) );
	}

private:
	UNUM32 id_{ 0 };

	std::map<std::string, NUM32> uniforms_;


	inline NUM32 getUniform( const char* uniform ) {

		auto it = uniforms_.find( uniform );

		if( it != uniforms_.end() ) {
			return it->second;
		}

		NUM32 uniformLocation = glGetUniformLocation( id_, uniform );
		uniforms_.emplace( std::string( uniform ), uniformLocation );

		return uniformLocation;
	}

};

GLenum to_glEnum( ShaderType type );
std::string to_string( ShaderType type );


}
}
