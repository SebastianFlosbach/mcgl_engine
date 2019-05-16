#pragma once

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "Mesh/Vertex.h"
#include "Rendering/Renderer.h"
#include "Texture/TextureAtlas.h"

namespace mesh {

class Mesh;

typedef std::unique_ptr<Mesh> Mesh_ptr;

class Mesh {
public:
	Mesh( const std::vector<Vertex>& vertices, const std::vector<UNUM32>& indices );
	Mesh( std::vector<Vertex>&& vertices, std::vector<UNUM32>&& indices );

	Mesh( const Mesh& other ) = delete;
	Mesh& operator=( const Mesh& other ) = delete;

	Mesh( Mesh&& other ) noexcept;
	Mesh& operator=( Mesh&& other ) noexcept;

	~Mesh();
	
	void draw( Renderer& renderer );

private:
	std::mutex mMesh_;
	bool isValid_{ false };
	bool isDeleted_{ false };
	bool isBufferGenerated_{ false };

	UNUM32 hVertexBuffer_{ 0 };
	UNUM32 hVertexArray_{ 0 };
	UNUM32 hElementBuffer_{ 0 };

	std::vector<Vertex> vertices_;
	std::vector<UNUM32> indices_;

	void generateGLData();

};



}
