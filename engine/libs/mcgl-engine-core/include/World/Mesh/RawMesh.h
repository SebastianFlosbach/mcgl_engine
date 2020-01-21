#pragma once

#include "BaseMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "World/Mesh/Vertex.h"

namespace world {
namespace mesh {


class RawMesh : public BaseMesh {
public:
	RawMesh( const std::vector<VertexC>& vertices, const std::vector<UNUM32>& indices );
	RawMesh( std::vector<VertexC>&& vertices, std::vector<UNUM32>&& indices );

	virtual ~RawMesh();

	RawMesh( const RawMesh& other ) = delete;
	RawMesh& operator=( const RawMesh& other ) = delete;

	RawMesh( RawMesh&& other ) noexcept;
	RawMesh& operator=( RawMesh&& other ) noexcept;

	virtual void draw( rendering::shader::IShader& shader, const rendering::Camera& camera ) const override;

private:
	virtual void generateGLData() override;

};


}
}
