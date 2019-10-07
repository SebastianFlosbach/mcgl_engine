#pragma once

#include "BaseMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "World/Mesh/Vertex.h"


namespace world {
namespace mesh {


class TexturedMesh : public BaseMesh {
public:
	TexturedMesh( const std::vector<VertexT>& vertices, const std::vector<UNUM32>& indices );
	TexturedMesh( std::vector<VertexT>&& vertices, std::vector<UNUM32>&& indices );

	virtual ~TexturedMesh();

	TexturedMesh( const TexturedMesh& other ) = delete;
	TexturedMesh& operator=( const TexturedMesh& other ) = delete;

	TexturedMesh( TexturedMesh&& other ) noexcept;
	TexturedMesh& operator=( TexturedMesh&& other ) noexcept;

	virtual void draw( rendering::shader::IShader& shader, const Camera& camera ) const override;

private:
	virtual void generateGLData() override;

};

typedef std::unique_ptr<TexturedMesh> TexturedMesh_ptr;


}
}
