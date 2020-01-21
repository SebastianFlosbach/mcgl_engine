#pragma once

#include "IMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "Vertex.h"

namespace world {
namespace mesh {


class BaseMesh : public IMesh {
public:
	BaseMesh() = default;
	virtual ~BaseMesh() = default;


	virtual void bind() override;
	virtual void unbind() override;

	virtual const glm::mat4& getModelMatrix() const override;

protected:
	BaseMesh( const std::vector<VertexCT>& vertices, const std::vector<UNUM32>& indices ); 
	BaseMesh( std::vector<VertexCT>&& vertices, std::vector<UNUM32>&& indices );

	std::mutex mMesh_;
	bool isValid_{ false };
	bool isDeleted_{ false };
	bool isBufferGenerated_{ false };

	glm::mat4 model_;

	UNUM32 hVertexBuffer_{ 0 };
	UNUM32 hVertexArray_{ 0 };
	UNUM32 hElementBuffer_{ 0 };

	std::vector<VertexCT> vertices_;
	std::vector<UNUM32> indices_;

	virtual void generateGLData() = 0;
};


}
}
