#pragma once

#include "IMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "World/Mesh/Vertex.h"

namespace world {
namespace mesh {


class RawMesh : public IMesh {
public:
	RawMesh( const std::vector<VertexC>& vertices, const std::vector<UNUM32>& indices );
	RawMesh( std::vector<VertexC>&& vertices, std::vector<UNUM32>&& indices );

	virtual ~RawMesh();

	RawMesh( const RawMesh& other ) = delete;
	RawMesh& operator=( const RawMesh& other ) = delete;

	RawMesh( RawMesh&& other ) noexcept;
	RawMesh& operator=( RawMesh&& other ) noexcept;

	virtual void bind() override;
	virtual void unbind() override;

	virtual void draw( rendering::shader::IShader& shader, const rendering::Camera& camera ) override;

	virtual const glm::mat4& getModelMatrix() const override;

private:
	std::mutex mMesh_;
	bool isValid_{ false };
	bool isDeleted_{ false };
	bool isBufferGenerated_{ false };

	glm::mat4 model_;

	UNUM32 hVertexBuffer_{ 0 };
	UNUM32 hVertexArray_{ 0 };
	UNUM32 hElementBuffer_{ 0 };

	std::vector<VertexC> vertices_;
	std::vector<UNUM32> indices_;

	void generateGLData();

};


}
}
