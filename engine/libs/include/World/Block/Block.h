#pragma once

#include <glm/glm.hpp>

namespace world {
namespace block {


constexpr float BLOCK_SIZE = 1.0f;

struct Block {
	bool isTransparent_ = true;
	unsigned int leftTexture_;
	unsigned int rightTexture_;
	unsigned int frontTexture_;
	unsigned int backTexture_;
	unsigned int topTexture_;
	unsigned int bottomTexture_;
};


}
}