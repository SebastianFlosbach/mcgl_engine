#pragma once
#include "glad/glad.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

struct __declspec( dllexport ) Texture {
public:
	Texture( const char* path ) {
		glGenTextures( 1, &hTexture_ );
		glBindTexture( GL_TEXTURE_2D, hTexture_ );
		// set the texture wrapping parameters
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		// set texture filtering parameters
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		unsigned char *data = stbi_load( path, &width, &height, &nrChannels, 0 );
		if ( data ) {
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
			glGenerateMipmap( GL_TEXTURE_2D );
		} else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free( data );
	}

	void bind() {
		glBindTexture( GL_TEXTURE_2D, hTexture_ );
	}

private:
	unsigned int hTexture_;

};