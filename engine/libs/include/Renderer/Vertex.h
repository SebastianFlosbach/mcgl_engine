#pragma once

constexpr unsigned int VERTEX_POSITION_SIZE = 3;
constexpr unsigned int VERTEX_TEXCOORD_SIZE = 2;

constexpr unsigned int VERTEX_SIZE = VERTEX_POSITION_SIZE + VERTEX_TEXCOORD_SIZE;


struct Vertex {
	float position_[VERTEX_POSITION_SIZE];
	float textureCoordinates_[VERTEX_TEXCOORD_SIZE];
};