#include "Mesh/SkyboxMesh.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>


namespace mesh {


const float SkyboxMesh::vertices_[] = {    
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

SkyboxMesh::SkyboxMesh( SkyboxMesh&& other ) noexcept {
	if( this == &other ) {
		return;
	}

	std::lock_guard<std::mutex> lock( mMesh_ );

	hVertexArray_ = other.hVertexArray_;
	hVertexBuffer_ = other.hVertexBuffer_;

	other.hVertexArray_ = 0;
	other.hVertexBuffer_ = 0;

	isValid_ = false;
}

SkyboxMesh& SkyboxMesh::operator=( SkyboxMesh&& other ) noexcept {
	return std::move( other );
}

SkyboxMesh::~SkyboxMesh() {
	glDeleteBuffers( 1, &hVertexBuffer_ );
	glDeleteVertexArrays( 1, &hVertexArray_ );
}

void SkyboxMesh::draw() {
	std::lock_guard<std::mutex> lock( mMesh_ );

	if( !isValid_ ) {
		generateGLData();
	}
}

void SkyboxMesh::bind() {
	if( !isValid_ ) {
		generateGLData();
	}

	glBindVertexArray( hVertexArray_ );
}

void SkyboxMesh::unbind() {
	glBindVertexArray( 0 );
}

void SkyboxMesh::generateGLData() {

	if( !isBufferGenerated_ ) {
		glGenVertexArrays( 1, &hVertexArray_ );
		glGenBuffers( 1, &hVertexBuffer_ );

		isBufferGenerated_ = true;
	}

	glBindVertexArray( hVertexArray_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer_ );

	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices_ ), &vertices_, GL_STATIC_DRAW );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
}


}
