#pragma once

#include "IMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "Mesh/Vertex.h"


namespace mesh {


class SkyboxMesh : public IMesh {
public:
	SkyboxMesh( const std::vector<Vertex>& vertices );
	SkyboxMesh( std::vector<Vertex>&& vertices );

	virtual ~SkyboxMesh();

	SkyboxMesh( const SkyboxMesh& other ) = delete;
	SkyboxMesh& operator=( const SkyboxMesh& other ) = delete;

	SkyboxMesh( SkyboxMesh&& other ) noexcept;
	SkyboxMesh& operator=( SkyboxMesh&& other ) noexcept;

	virtual void draw() override;

private:
	std::mutex mMesh_;
	bool isValid_{ false };
	bool isDeleted_{ false };
	bool isBufferGenerated_{ false };

	UNUM32 hVertexBuffer_{ 0 };
	UNUM32 hVertexArray_{ 0 };

	std::vector<Vertex> vertices_;

	void generateGLData();

};


}
