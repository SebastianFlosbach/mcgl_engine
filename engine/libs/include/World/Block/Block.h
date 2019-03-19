#pragma once

#include <glm/glm.hpp>

namespace world {
namespace block {

constexpr float BLOCK_SIZE = 1.0f;

struct Block {
	glm::vec<3, int> position_;
	bool isTransparent_;
};

}
}