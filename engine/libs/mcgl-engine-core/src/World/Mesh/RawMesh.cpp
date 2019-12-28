#include "Mesh/RawMesh.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace world {
namespace mesh {


RawMesh::RawMesh( const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices ) :
	vertices_( vertices ), indices_( indices ) {}

RawMesh::RawMesh( std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices ) :
	vertices_( std::move( vertices ) ), indices_( std::move( indices ) ) {}

RawMesh::RawMesh( RawMesh&& other ) noexcept {
	if( this == &other ) {
		return;
	}

	vertices_ = std::move( other.vertices_ );
	indices_ = std::move( other.indices_ );

	std::lock_guard<std::mutex> lock( mMesh_ );

	hVertexArray_ = other.hVertexArray_;
	hVertexBuffer_ = other.hVertexBuffer_;
	hElementBuffer_ = other.hElementBuffer_;

	other.hVertexArray_ = 0;
	other.hVertexBuffer_ = 0;
	other.hElementBuffer_ = 0;

	isValid_ = false;
}

RawMesh& RawMesh::operator=( RawMesh&& other ) noexcept {
	return std::move( other );
}

RawMesh::~RawMesh() {
	glDeleteBuffers( 1, &hVertexBuffer_ );
	glDeleteBuffers( 1, &hElementBuffer_ );
	glDeleteVertexArrays( 1, &hVertexArray_ );
}

void RawMesh::draw() {
	std::lock_guard<std::mutex> lock( mMesh_ );

	if( !isValid_ ) {
		generateGLData();
	}

	glBindVertexArray( hVertexArray_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer_ );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hElementBuffer_ );

	glDrawElements( GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );
}

void RawMesh::generateGLData() {

	if( !isBufferGenerated_ ) {
		glGenBuffers( 1, &hVertexBuffer_ );
		glGenBuffers( 1, &hElementBuffer_ );
		glGenVertexArrays( 1, &hVertexArray_ );

		isBufferGenerated_ = true;
	}

	glBindVertexArray( hVertexArray_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer_ );

	glBufferData( GL_ARRAY_BUFFER, vertices_.size() * sizeof( Vertex ), &vertices_[0], GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hElementBuffer_ );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof( unsigned int ), &indices_[0], GL_STATIC_DRAW );

	// vertex positions
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );

	isValid_ = true;
}


}
}
