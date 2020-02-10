#include "Texture/Texture.h"

#include "Helper/OpenGLDebug.h"
#include "Texture/StbImageWrapper.h"

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
	unsigned char* data = createImageData( path, width_, height_, true );
	if ( data ) {
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap( GL_TEXTURE_2D );
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	destroyImageData( data );
}

Texture::Texture( const std::string& path ) : Texture( path.c_str() ) {
}


}