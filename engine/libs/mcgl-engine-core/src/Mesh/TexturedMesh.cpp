#include "Mesh/TexturedMesh.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>


namespace mesh {


TexturedMesh::TexturedMesh( const std::vector<VertexT>& vertices, const std::vector<UNUM32>& indices ) :
	vertices_( vertices ), indices_( indices ) {
}

TexturedMesh::TexturedMesh( std::vector<VertexT>&& vertices, std::vector<UNUM32>&& indices ) :
	vertices_( std::move( vertices ) ), indices_( std::move( indices ) ) {
}

TexturedMesh::TexturedMesh( TexturedMesh&& other ) noexcept {
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

TexturedMesh& TexturedMesh::operator=( TexturedMesh&& other ) noexcept {
	return std::move( other );
}

TexturedMesh::~TexturedMesh() {
	glDeleteBuffers( 1, &hVertexBuffer_ );
	glDeleteBuffers( 1, &hElementBuffer_ );
	glDeleteVertexArrays( 1, &hVertexArray_ );
}

void TexturedMesh::generateGLData() {

	if( !isBufferGenerated_ ) {
		glGenBuffers( 1, &hVertexBuffer_ );
		glGenBuffers( 1, &hElementBuffer_ );
		glGenVertexArrays( 1, &hVertexArray_ );

		isBufferGenerated_ = true;
	}

	glBindVertexArray( hVertexArray_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer_ );

	glBufferData( GL_ARRAY_BUFFER, vertices_.size() * sizeof( VertexT ), &vertices_[0], GL_DYNAMIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hElementBuffer_ );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof( unsigned int ), &indices_[0], GL_DYNAMIC_DRAW );

	// vertex positions
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( VertexT ), (void*)0 );

	// vertex texture coords
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( VertexT ), (void*)offsetof( VertexT, texCoords_ ) );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );

	isValid_ = true;
}

void TexturedMesh::draw() {
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


}