#pragma once

#include <vector>

#include "Face.h"
#include "Vertex.h"

class Mesh {
public:
	void addFace( const Face& face ) {
		faces_.push_back( face );
	}

private:
	std::vector<Face> faces_;
	std::vector<Vertex> vertices_;

};