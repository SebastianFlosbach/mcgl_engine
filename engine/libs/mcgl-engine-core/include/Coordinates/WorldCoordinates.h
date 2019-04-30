#pragma once

#include <glm/glm.hpp>

namespace coordinates {


struct WorldCoordinates {
public:
	WorldCoordinates( float x, float y, float z ) : x_( x ), y_( y ), z_( z ) {}

	
	glm::vec3 toVec3() const {
		return { x_, y_, z_ };
	}

	float x_, y_, z_;

};


}