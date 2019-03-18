#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Face;

struct Vertex {
	glm::vec3 position_;
	//glm::vec3 normal_;
	glm::vec2 texCoords_;
};