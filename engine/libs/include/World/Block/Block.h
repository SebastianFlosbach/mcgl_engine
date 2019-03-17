#pragma once

#include <glm/glm.hpp>

constexpr unsigned int BLOCK_SIZE = 1;

struct Block {
	glm::vec<3, int> position_;
};