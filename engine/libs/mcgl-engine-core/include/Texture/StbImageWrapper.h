#pragma once


namespace texture {


unsigned char* createImageData( const char* path, int& width, int& height, bool flipVertically );
void destroyImageData( unsigned char* data );


}
