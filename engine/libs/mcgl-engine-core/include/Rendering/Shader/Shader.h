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

	void compile();

private:
	inline void addShader( const std::string& path, GLenum type );

};

typedef std::unique_ptr<Shader> Shader_ptr;


}
}
