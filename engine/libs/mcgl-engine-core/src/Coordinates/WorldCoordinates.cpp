#include "Coordinates/WorldCoordinates.h"


namespace coordinates {


WorldCoordinates::WorldCoordinates( float x, float y, float z ) : x_( x ), y_( y ), z_( z ) {}


glm::vec3 WorldCoordinates::toVec3() const {
	return { x_, y_, z_ };
}


}