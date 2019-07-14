#pragma once

#include "IMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"


namespace mesh {


class BaseMesh : public IMesh {
public:
	BaseMesh() = default;
	virtual ~BaseMesh() = default;


	virtual void bind() override;
	virtual void unbind() override;

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

	std::vector<Vertex> vertices_;
	std::vector<UNUM32> indices_;

	virtual void generateGLData() = 0;
};


}