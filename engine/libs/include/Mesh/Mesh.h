#pragma once

#include <vector>

#include "../Texture/TextureAtlas.h"
#include "Vertex.h"
#include "../Renderer/Renderer.h"

class Mesh {
public:
	Mesh( const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const texture::TextureAtlas& textureAtlas );
	Mesh( std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, const texture::TextureAtlas& textureAtlas );

	Mesh( const Mesh& other ) = delete;
	Mesh& operator=( const Mesh& other ) = delete;

	Mesh( Mesh&& other ) : textureAtlas_( other.textureAtlas_ ) {
		*this = std::move( other );
	}

	Mesh& operator=( Mesh&& other ) {
		this->hVertexBuffer_ = other.hVertexBuffer_;
		this->hVertexArray_ = other.hVertexArray_;
		this->hElementBuffer_ = other.hElementBuffer_;

		this->vertices_ = std::move( other.vertices_ );
		this->indices_ = std::move( other.indices_ );

		return *this;
	}

	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	const texture::TextureAtlas& textureAtlas_;
	
	void draw( Renderer& renderer );
private:
	/*  Render data  */
	unsigned int hVertexBuffer_;
	unsigned int hVertexArray_;
	unsigned int hElementBuffer_;

	/*  Functions    */
	void setupMesh();
};


typedef std::unique_ptr<Mesh> Mesh_ptr;