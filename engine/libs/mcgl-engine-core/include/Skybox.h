#pragma once

#include "CubeMap.h"
#include "Mesh/SkyboxMesh.h"
#include "Rendering/Renderer.h"


class Skybox {
public:
	Skybox( const std::vector<std::string>& faces ) : cubeMap_( faces ) {
		pCubeMesh_ = std::unique_ptr<mesh::IMesh>(
			new mesh::SkyboxMesh( vertices_ )
		);
	}

	void draw( Renderer& renderer ) {
		//glDepthMask( GL_FALSE );
		renderer.use( ShaderType::Skybox );
		cubeMap_.bind();
		pCubeMesh_->draw();
		//glDepthMask( GL_TRUE );
	}

private:
	CubeMap cubeMap_;
	mesh::IMesh_ptr pCubeMesh_;

	static const std::vector<Vertex> vertices_;

};

typedef std::unique_ptr<Skybox> Skybox_ptr;
