#include "Skybox.h"


const std::vector<Vertex> Skybox::vertices_ = {
	{ -1.0, -1.0, -1.0 },
	{  1.0, -1.0, -1.0 },
	{  1.0,  1.0, -1.0 },
	{ -1.0,  1.0, -1.0 },
	{ -1.0, -1.0,  1.0 },
	{  1.0, -1.0,  1.0 },
	{  1.0,  1.0,  1.0 },
	{ -1.0,  1.0,  1.0 },
};

const std::vector<UNUM32> Skybox::indices_ ={
	// Right
	1, 5, 6,
	1, 6, 2,
	// Left
	4, 0, 3,
	4, 3, 7,
	// Top
	3, 2, 7,
	2, 6, 7,
	// Bottom
	0, 4, 1,
	1, 4, 5,
	// Front
	0, 1, 2,
	0, 2, 3,
	// Back
	5, 4, 7,
	5, 7, 6
};
