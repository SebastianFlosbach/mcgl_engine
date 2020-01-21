#pragma once

#include "CubeMap.h"
#include "World/Mesh/SkyboxMesh.h"
#include "Rendering/Renderer.h"


class Skybox {
public:
	Skybox( const std::vector<std::string>& faces ) : cubeMap_( faces ) {
		pCubeMesh_ = std::unique_ptr<world::mesh::IMesh>(
			new world::mesh::SkyboxMesh()
		);
	}

	void draw( rendering::Renderer& renderer ) {
		pCubeMesh_->bind();
		glActiveTexture( GL_TEXTURE0 );
		cubeMap_.bind();
		glDrawArrays( GL_TRIANGLES, 0, 36 );
		pCubeMesh_->unbind();
	}

private:
	CubeMap cubeMap_;
	world::mesh::IMesh_ptr pCubeMesh_;

};

typedef std::unique_ptr<Skybox> Skybox_ptr;
