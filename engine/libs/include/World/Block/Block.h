#pragma once

#include <glm/glm.hpp>

namespace world {
namespace block {

constexpr float BLOCK_SIZE = 1.0f;

struct Block {
	bool isTransparent_ = true;
};

}
}