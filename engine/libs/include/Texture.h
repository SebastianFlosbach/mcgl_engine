#pragma once
#include <glad/glad.h>
#include <iostream>

struct Texture {
public:
	Texture( const char* path );

	Texture( const Texture& other ) = delete;
	Texture& operator=( const Texture& other ) = delete;

	Texture( Texture&& other ) {
		*this = std::move( other );
	}

	Texture& operator=( Texture&& other ) {
		this->hTexture_ = other.hTexture_;

		// Cleanup to avoid texture being reused or deleted
		other.hTexture_ = 0;

		return *this;
	}

	~Texture() {
		glDeleteTextures( 1, &hTexture_ );
	}

	void bind() {
		glBindTexture( GL_TEXTURE_2D, hTexture_ );
	}

	unsigned int get() {
		return hTexture_;
	}

private:
	unsigned int hTexture_;

};