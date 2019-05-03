#pragma once

#include <glm/glm.hpp>


namespace coordinates {
struct BlockCoordinates;
struct ChunkCoordinates;

struct WorldCoordinates {
public:
	WorldCoordinates( float x, float y, float z );
	WorldCoordinates( const glm::vec3 position );
	
	glm::vec3 toVec3() const;

	ChunkCoordinates toChunkCoordinates() const;

	float x_, y_, z_;

};


}

namespace std {

template<>
struct hash<coordinates::WorldCoordinates> {
	size_t operator()( const coordinates::WorldCoordinates& coords ) const noexcept {
		size_t x = std::hash<double>()(coords.x_);
		size_t y = std::hash<double>()(coords.y_);
		size_t z = std::hash<double>()(coords.z_);

		return (x ^ (y << 1)) ^ z;
	}
};

template<>
struct equal_to<coordinates::WorldCoordinates> {
	constexpr bool operator()( const coordinates::WorldCoordinates& left, const coordinates::WorldCoordinates& right ) const {	// apply operator== to operands
		return left.x_ == right.x_ && left.z_ == right.z_ && left.y_ == right.y_;
	}
};

}