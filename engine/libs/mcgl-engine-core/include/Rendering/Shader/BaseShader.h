#pragma once

#include "IShader.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <map>


namespace rendering{
namespace shader {


class BaseShader: public IShader {
public:
	virtual UNUM32 id() const override {
		return id_;
	}

	virtual void addShader( const std::string& path, ShaderType type ) = 0;

	virtual void compile() = 0;

	virtual void use() override {
		glUseProgram( id_ );
	}

	virtual void setUniformInt( const char* uniform, NUM32 value ) override {
		glUniform1i( getUniform( uniform ), value );
	}

	void setUniformMat4f( const char* uniform, const glm::mat4& matrix ) override {
		glUniformMatrix4fv( getUniform( uniform ), 1, GL_FALSE, glm::value_ptr( matrix ) );
	}

private:
	UNUM32 id_;

	std::map<std::string, NUM32> uniforms_;


	inline NUM32 getUniform( const char* uniform ) {

		auto it = uniforms_.find( uniform );

		if( it != uniforms_.end() ) {
			return it->second;
		}

		NUM32 uniformLocation = glGetUniformLocation( hShaderProgramm_, uniform );
		uniforms_.emplace( std::string( uniform ), uniformLocation );

		return uniformLocation;
	}

};


}
}
