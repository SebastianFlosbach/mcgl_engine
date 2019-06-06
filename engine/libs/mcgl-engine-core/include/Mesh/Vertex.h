#pragma once

#include <glm/glm.hpp>


struct Vertex {
	glm::vec3 position_;
};

struct VertexT : public Vertex {
	glm::vec2 texCoords_;
};
