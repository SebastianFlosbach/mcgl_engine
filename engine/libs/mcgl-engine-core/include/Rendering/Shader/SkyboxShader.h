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


class SkyboxShader : BaseShader {
public:
	// Default constructor
	SkyboxShader() = default;
	~SkyboxShader() = default;

	// Copy constructor
	SkyboxShader( const SkyboxShader& other ) = delete;
	SkyboxShader& operator=( const SkyboxShader& other ) = delete;

	// Move constructor
	SkyboxShader( SkyboxShader&& other ) noexcept;
	SkyboxShader& operator=( SkyboxShader&& other ) noexcept;

	virtual Type type() const override {
		return Type::Chunk;
	}

	virtual void addShader( const std::string& path, ShaderType type ) override;
	void compile();

private:
	glm::mat4 model_ = glm::mat4( 1.0f );
	glm::mat4 view_ = glm::mat4( 1.0f );
	glm::mat4 projection_ = glm::perspective( glm::radians( 45.0f ), 800.f / 600.f, 0.1f, 500.0f );

};

typedef std::unique_ptr<SkyboxShader> SkyboxShader_ptr;


}
}
