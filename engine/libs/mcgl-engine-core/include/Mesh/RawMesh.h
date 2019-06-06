#pragma once

#include "IMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "Mesh/Vertex.h"


namespace mesh {


class RawMesh : public IMesh {
public:
	RawMesh( const std::vector<Vertex>& vertices, const std::vector<UNUM32>& indices );
	RawMesh( std::vector<Vertex>&& vertices, std::vector<UNUM32>&& indices );

	virtual ~RawMesh();

	RawMesh( const RawMesh& other ) = delete;
	RawMesh& operator=( const RawMesh& other ) = delete;

	RawMesh( RawMesh&& other ) noexcept;
	RawMesh& operator=( RawMesh&& other ) noexcept;

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
