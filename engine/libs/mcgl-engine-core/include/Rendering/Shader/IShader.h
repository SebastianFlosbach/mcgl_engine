#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

#include "Definition/mcgl_engine_def.h"


namespace rendering {
namespace shader {


enum class ShaderType {
	Vertex,
	Fragment
};

enum class Type {
	Chunk,
	Skybox
};


class IShader {
public:
	virtual ~IShader() = default;

	virtual UNUM32 id() const = 0;
	virtual Type type() const = 0;

	virtual void addShader( const std::string& path, ShaderType type ) = 0;

	virtual void compile() = 0;

	virtual void use() = 0;

	virtual void setUniformInt( const char* uniform, NUM32 value ) = 0;
	virtual void setUniformMat4f( const char* uniform, const glm::mat4& matrix ) = 0;

};

typedef std::unique_ptr<IShader> IShader_ptr;


}
}
