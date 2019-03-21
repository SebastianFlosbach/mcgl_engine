#include "Texture/Texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

namespace texture {


Texture::Texture( const char* path ) {
	glGenTextures( 1, &hTexture_ );
	glBindTexture( GL_TEXTURE_2D, hTexture_ );
	// set the texture wrapping parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	// set texture filtering parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load( true );
	int nrChannels;
	unsigned char *data = stbi_load( path, &width_, &height_, &nrChannels, 0 );
	if ( data ) {
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap( GL_TEXTURE_2D );
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free( data );
}

Texture::Texture( const std::string& path ) : Texture( path.c_str() ) {
}


}