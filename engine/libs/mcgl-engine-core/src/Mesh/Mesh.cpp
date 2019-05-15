#include "Mesh/Mesh.h"

#include "Helper/OpenGLDebug.h"


namespace mesh {


Mesh::Mesh( const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices ) :
	vertices_( vertices ), indices_( indices ) {
}

Mesh::Mesh( std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices ) :
	vertices_( std::move( vertices ) ), indices_( std::move( indices ) ) {
}

Mesh::Mesh( Mesh&& other ) noexcept {
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

Mesh& Mesh::operator=( Mesh&& other ) noexcept {
	return std::move( other );
}

Mesh::~Mesh() {
	glDeleteBuffers( 1, &hVertexBuffer_ );
	glDeleteBuffers( 1, &hElementBuffer_ );
	glDeleteVertexArrays( 1, &hVertexArray_ );
}

void Mesh::generateGLData() {

	if( !isBufferGenerated_ ) {
		glGenBuffers( 1, &hVertexBuffer_ );
		glGenBuffers( 1, &hElementBuffer_ );
		glGenVertexArrays( 1, &hVertexArray_ );

		isBufferGenerated_ = true;
	}

	glBindVertexArray( hVertexArray_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer_ );

	glBufferData( GL_ARRAY_BUFFER, vertices_.size() * sizeof( Vertex ), &vertices_[0], GL_DYNAMIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hElementBuffer_ );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof( unsigned int ), &indices_[0], GL_DYNAMIC_DRAW );

	// vertex positions
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)0 );

	// vertex texture coords
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)offsetof( Vertex, texCoords_ ) );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );

	isValid_ = true;
}

void Mesh::draw( Renderer& renderer ) {
	renderer.use();

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