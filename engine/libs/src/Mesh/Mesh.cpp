#include "Mesh/Mesh.h"

Mesh::Mesh( const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const texture::TextureAtlas& textureAtlas, const glm::vec3& position ) : 
	vertices_( vertices ), indices_( indices ), textureAtlas_( textureAtlas ), position_( position ) {
	setupMesh();
}

Mesh::Mesh( std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, const texture::TextureAtlas& textureAtlas, const glm::vec3& position ) :
	vertices_( std::move( vertices ) ), indices_( std::move( indices ) ), textureAtlas_( textureAtlas ), position_( position ) {
	setupMesh();
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
	glm::mat4 model = glm::mat4( 1.0f );
	model = glm::translate( model, position_ );

	renderer.setModelMatrix( model );
	renderer.update();

	glActiveTexture( GL_TEXTURE0 );
	renderer.bindTexture();

	glBindVertexArray( hVertexBuffer_ );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexArray_ );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hElementBuffer_ );
	glDrawElements( GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0 );
	glBindVertexArray( 0 );
}