#pragma once

#include <vector>

#include <glad/glad.h>

#include "Vertex.h"


struct VertexBuffer {
public:
	VertexBuffer( float* data, unsigned int size ) {
		glGenVertexArrays( 1, &hVertexArray_ );
		glGenBuffers( 1, &hVertexBuffer_ );

		glBindVertexArray( hVertexArray_ );

		glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer_ );
		glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );

		glVertexAttribPointer( 0, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, VERTEX_POSITION_SIZE * sizeof( float ), (void*)0 );
		glVertexAttribPointer( 1, VERTEX_TEXCOORD_SIZE, GL_FLOAT, GL_FALSE, VERTEX_TEXCOORD_SIZE * sizeof( float ), (void*)(VERTEX_POSITION_SIZE * sizeof( float ) ) );

		glEnableVertexAttribArray( 0 );
		glEnableVertexAttribArray( 1 );
	}

	VertexBuffer( const VertexBuffer& other ) = delete;
	VertexBuffer& operator=( const VertexBuffer& other ) = delete;

	void createElementBuffer( unsigned int* data, unsigned int size ) {
		glGenBuffers( 1, &hElementBuffer_ );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hElementBuffer_ );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );

		useElementBuffer_ = true;
	}

	void bind() {
		glBindVertexArray( hVertexArray_ );
		if ( useElementBuffer_ ) {
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hElementBuffer_ );
		}
	}

	void unbind() {
		glBindVertexArray( NULL );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, NULL );
	}

	unsigned int getBufferHandle() {
		return hVertexBuffer_;
	}

	unsigned int getArrayHandle() {
		return hVertexArray_;
	}

	unsigned int getElementHandle() {
		return hElementBuffer_;
	}

private:
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;

	unsigned int hVertexBuffer_;
	unsigned int hVertexArray_;

	bool useElementBuffer_ = false;
	unsigned int hElementBuffer_;

};