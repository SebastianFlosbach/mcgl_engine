#pragma once

#include <string>

#include "Definition/mcgl_engine_def.h"


namespace rendering {
namespace shader {


enum class Type {
	Vertex,
	Fragment
};



class IShader {
public: 
	virtual UNUM32 id() const = 0;

	virtual void addShader( const std::string& path, Type type ) = 0;

	virtual void compile() = 0;

	virtual void use() = 0

	virtual void setUniformInt( const char* uniform, NUM32 value ) = 0;
	virtual void setUniformMat4f( const char* uniform, const glm::mat4& matrix ) = 0;

};


}
}
