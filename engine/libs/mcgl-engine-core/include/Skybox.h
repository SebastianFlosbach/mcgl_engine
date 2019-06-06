#pragma once

#include "CubeMap.h"
#include "Mesh/SkyboxMesh.h"
#include "Renderer/Renderer.h"


class Skybox {
public:
	Skybox( const std::vector<std::string>& faces ) : cubeMap_( faces ) {
		pCubeMesh_ = std::unique_ptr<mesh::Mesh>(
			new mesh::SkyboxMesh();
		);
	}

	void draw( Renderer& renderer ) {
		glDepthMask( GL_FALSE );
		renderer.use( ShaderType::Skybox );
		cubeMap_.bind();
		pCubeMesh_->draw();
		glDepthMask( GL_TRUE );
	}

private:
	CubeMap cubeMap_;
	mesh::Mesh_ptr pCubeMesh_;

	constexpr float vertices[] = {
		-1.0, -1.0, -1.0,
		 1.0, -1.0, -1.0,
		 1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
		-1.0, -1.0,  1.0,
		 1.0, -1.0,  1.0,
		 1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,	
	};

	constexpr UNUM32 indices[] ={
		// Right
		1, 5, 6
		1, 6, 2
		// Left
		4, 0, 3
		4, 3, 7
		// Top
		3, 2, 7,
		2, 6, 7,
		// Bottom
		0, 4, 1,
		1, 4, 5,
		// Front
		0, 1, 2,
		0, 2, 3,
		// Back
		5, 4, 7,
		5, 7, 6
	};

};
