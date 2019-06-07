#pragma once

#include <glm/glm.hpp>


struct Vertex {
	Vertex( float x, float y, float z ) : position_( x, y, z ) {}
	virtual ~Vertex() = default;

	glm::vec3 position_;
};

struct VertexT : public Vertex {
	VertexT( float x, float y, float z, float t, float u ) : Vertex( x, y, z ), texCoords_( t, u ) {}
	virtual ~VertexT() = default;

	glm::vec2 texCoords_;
};
