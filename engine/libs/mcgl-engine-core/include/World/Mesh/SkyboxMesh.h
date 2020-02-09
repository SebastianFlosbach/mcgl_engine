#pragma once

#include "IMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "World/Mesh/Vertex.h"


namespace world {
namespace mesh {


class SkyboxMesh : public IMesh {
public:
	SkyboxMesh() = default;

	virtual ~SkyboxMesh();

	SkyboxMesh( const SkyboxMesh& other ) = delete;
	SkyboxMesh& operator=( const SkyboxMesh& other ) = delete;

	SkyboxMesh( SkyboxMesh&& other ) noexcept;
	SkyboxMesh& operator=( SkyboxMesh&& other ) noexcept;

	virtual void draw( rendering::shader::IShader& shader, const rendering::Camera& camera ) override;
	virtual void bind() override;
	virtual void unbind() override;

	virtual const glm::mat4& getModelMatrix() const override;

private:
	std::mutex mMesh_;
	bool isValid_{ false };
	bool isDeleted_{ false };
	bool isBufferGenerated_{ false };

	UNUM32 hVertexBuffer_{ 0 };
	UNUM32 hVertexArray_{ 0 };

	static const float vertices_[];

	void generateGLData();

};


}
}
