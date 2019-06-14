#pragma once

#include "BaseShader.h"

#include <fstream>
#include <map>
#include <string>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Definition/mcgl_engine_def.h"


namespace rendering {
namespace shader {


class ChunkShader : BaseShader {
public:
	// Default constructor
	ChunkShader() = default;
	~ChunkShader() = default;

	// Copy constructor
	ChunkShader( const ChunkShader& other ) = delete;
	ChunkShader& operator=( const ChunkShader& other ) = delete;

	// Move constructor
	ChunkShader( ChunkShader&& other ) noexcept;
	ChunkShader& operator=( ChunkShader&& other ) noexcept;

	virtual Type type() const override {
		return Type::Chunk;
	}

	virtual void addShader( const std::string& path, ShaderType type ) override;
	void compile();

private:
	inline void addShader( const std::string& path, GLenum type );

};

typedef std::unique_ptr<ChunkShader> ChunkShader_ptr;


}
}
