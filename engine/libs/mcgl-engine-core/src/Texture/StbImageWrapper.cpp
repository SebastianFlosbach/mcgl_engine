#include "Texture/StbImageWrapper.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif


namespace texture {


unsigned char* createImageData( const char* path, int& width, int& height, bool flipVertically ) {
	stbi_set_flip_vertically_on_load( flipVertically );
	int nrChannels;
	return stbi_load( path, &width, &height, &nrChannels, 0 );
}

void destroyImageData( unsigned char* data ) {
	stbi_image_free( data );
}


}
