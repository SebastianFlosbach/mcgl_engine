#include "Mesh/Mesh.h"


namespace mesh {


Mesh::Mesh( const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices ) : 
	vertices_( vertices ), indices_( indices ) {
	//setupMesh();
}

Mesh::Mesh( std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices ) :
	vertices_( std::move( vertices ) ), indices_( std::move( indices ) ) {
	//setupMesh();
}

Mesh::Mesh( Mesh&& other ) noexcept :
	hVertexArray_( other.hVertexArray_ ),
	hVertexBuffer_( other.hVertexBuffer_ ),
	hElementBuffer_( other.hElementBuffer_ ),
	vertices_( std::move( other.vertices_ ) ),
	indices_( std::move( other.indices_ ) )
{
	if( this == &other ) {
		return;
	}

	other.hVertexArray_ = 0;
	other.hVertexBuffer_ = 0;
	other.hElementBuffer_ = 0;
}

Mesh& Mesh::operator=( Mesh&& other ) noexcept {
	return std::move( other );
}

Mesh::~Mesh() {
	glDeleteBuffers( 1, &hVertexBuffer_ );
	glDeleteBuffers( 1, &hElementBuffer_ );
	glDeleteVertexArrays( 1, &hVertexArray_ );
}

void Mesh::setupMesh() {
	glGenVertexArrays( 1, &hVertexBuffer_ );
	glGenBuffers( 1, &hVertexArray_ );
	glGenBuffers( 1, &hElementBuffer_ );

	glBindVertexArray( hVertexBuffer_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexArray_ );

	glBufferData( GL_ARRAY_BUFFER, vertices_.size() * sizeof( Vertex ), &vertices_[0], GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hElementBuffer_ );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof( unsigned int ), &indices_[0], GL_STATIC_DRAW );

	// vertex positions
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) 0 );
	// vertex normals
	//glEnableVertexAttribArray( 1 );
	//glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) offsetof( Vertex, normal_ ) );
	// vertex texture coords
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) offsetof( Vertex, texCoords_ ) );

	glBindVertexArray( 0 );
}

void Mesh::draw( Renderer& renderer ) {
	renderer.use();

	glBindVertexArray( hVertexBuffer_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexArray_ );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hElementBuffer_ );
	glDrawElements( GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0 );
	glBindVertexArray( 0 );
}


}