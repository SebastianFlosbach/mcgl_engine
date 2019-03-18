#pragma once

#include <vector>

#include "../Texture.h"
#include "Vertex.h"
#include "../Shader.h"

class Mesh {
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	Texture texture_;
	/*  Functions  */
	Mesh( const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture&& texture );

	Mesh( const Mesh& other ) = delete;
	Mesh& operator=( const Mesh& other ) = delete;

	void Draw( Shader& shader );
private:
	/*  Render data  */
	unsigned int hVertexBuffer_;
	unsigned int hVertexArray_;
	unsigned int hElementBuffer_;

	/*  Functions    */
	void setupMesh();
};