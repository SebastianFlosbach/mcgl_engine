#include "Mesh/SkyboxMesh.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>


namespace mesh {


SkyboxMesh::SkyboxMesh( const std::vector<Vertex>& vertices ) :
	vertices_( vertices ) {}

SkyboxMesh::SkyboxMesh( std::vector<Vertex>&& vertices ) :
	vertices_( std::move( vertices ) ) {}

SkyboxMesh::SkyboxMesh( SkyboxMesh&& other ) noexcept {
	if( this == &other ) {
		return;
	}

	vertices_ = std::move( other.vertices_ );

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

	glDepthFunc( GL_LEQUAL );

	glBindVertexArray( hVertexArray_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer_ );

	glDrawArrays( GL_TRIANGLES, vertices_.size(), GL_UNSIGNED_INT );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );

	glDepthFunc( GL_LESS );
}

void SkyboxMesh::generateGLData() {

	if( !isBufferGenerated_ ) {
		glGenBuffers( 1, &hVertexBuffer_ );
		glGenVertexArrays( 1, &hVertexArray_ );

		isBufferGenerated_ = true;
	}

	glBindVertexArray( hVertexArray_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer_ );

	glBufferData( GL_ARRAY_BUFFER, vertices_.size() * sizeof( Vertex ), &vertices_[0], GL_STATIC_DRAW );

	// vertex positions
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );

	isValid_ = true;
}


}
