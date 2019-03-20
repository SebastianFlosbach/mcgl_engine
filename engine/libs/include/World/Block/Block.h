#pragma once

#include <glm/glm.hpp>

namespace world {
namespace block {


constexpr float BLOCK_SIZE = 1.0f;

struct Block {
	bool isTransparent_ = true;
	unsigned int leftTexture_ = 2;
	unsigned int rightTexture_ = 2;
	unsigned int frontTexture_ = 2;
	unsigned int backTexture_ = 2;
	unsigned int topTexture_ = 0;
	unsigned int bottomTexture_ = 1;
};


}
}