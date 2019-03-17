#pragma once

#include <vector>

struct Face;

struct Vertex {
	std::vector<Face*> faces_;
};