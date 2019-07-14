#pragma once

#include "BaseMesh.h"

#include <mutex>
#include <vector>

#include "Definition/mcgl_engine_def.h"
#include "Mesh/Vertex.h"


namespace mesh {


class RawMesh : public BaseMesh {
public:
	RawMesh( const std::vector<Vertex>& vertices, const std::vector<UNUM32>& indices );
	RawMesh( std::vector<Vertex>&& vertices, std::vector<UNUM32>&& indices );

	virtual ~RawMesh();

	RawMesh( const RawMesh& other ) = delete;
	RawMesh& operator=( const RawMesh& other ) = delete;

	RawMesh( RawMesh&& other ) noexcept;
	RawMesh& operator=( RawMesh&& other ) noexcept;

	virtual void draw( rendering::shader::IShader& shader, const Camera& camera ) const override;

private:
	virtual void generateGLData() override;

};


}
