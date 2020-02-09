#pragma once

#include "IMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "World/Mesh/Vertex.h"


namespace world {
namespace mesh {


class TexturedMesh : public IMesh {
public:
	TexturedMesh( const std::vector<VertexCT>& vertices, const std::vector<UNUM32>& indices );
	TexturedMesh( std::vector<VertexCT>&& vertices, std::vector<UNUM32>&& indices );

	virtual ~TexturedMesh();

	TexturedMesh( const TexturedMesh& other ) = delete;
	TexturedMesh& operator=( const TexturedMesh& other ) = delete;

	TexturedMesh( TexturedMesh&& other ) noexcept;
	TexturedMesh& operator=( TexturedMesh&& other ) noexcept;

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

	std::vector<VertexCT> vertices_;
	std::vector<UNUM32> indices_;

	void generateGLData();

};

typedef std::unique_ptr<TexturedMesh> TexturedMesh_ptr;


}
}
