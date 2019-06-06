#pragma once

#include "IMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "Mesh/Vertex.h"


namespace mesh {


class TexturedMesh : public IMesh {
public:
	TexturedMesh( const std::vector<VertexT>& vertices, const std::vector<UNUM32>& indices );
	TexturedMesh( std::vector<VertexT>&& vertices, std::vector<UNUM32>&& indices );
	
	virtual ~TexturedMesh();

	TexturedMesh( const TexturedMesh& other ) = delete;
	TexturedMesh& operator=( const TexturedMesh& other ) = delete;

	TexturedMesh( TexturedMesh&& other ) noexcept;
	TexturedMesh& operator=( TexturedMesh&& other ) noexcept;

	virtual void draw() override;

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
