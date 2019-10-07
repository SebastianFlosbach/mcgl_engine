#pragma once

#include <glm/glm.hpp>


namespace world {
namespace mesh {


struct VertexC {
	VertexC( float x, float y, float z ) : position_( x, y, z ){}

	glm::vec3 position_;
};

struct VertexCT {
	VertexCT( float x, float y, float z, float t, float r ) : position_( x, y, z ), texCoords_( t, r ){}

	glm::vec3 position_;
	glm::vec2 texCoords_;
};


}
}
