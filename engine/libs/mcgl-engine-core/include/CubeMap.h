#pragma once
#include "glad/glad.h"

#include <vector>

#include "Rendering/Renderer.h"
#include "Texture/StbImageWrapper.h"

#include "Helper/OpenGLDebug.h"


struct CubeMap {
public:
	CubeMap( const std::vector<std::string>& faces ) {
		loadCubemap( faces );
	}

	void bind() {
		glBindTexture( GL_TEXTURE_CUBE_MAP, hCubeMap_ );
	}

private:
	UNUM32 hCubeMap_;

	void loadCubemap( const std::vector<std::string>& faces ) {
		glGenTextures( 1, &hCubeMap_ );
		glBindTexture( GL_TEXTURE_CUBE_MAP, hCubeMap_ );

		int width, height;
		for( unsigned int i = 0; i < faces.size(); i++ )
		{
			unsigned char* data = texture::createImageData( faces[i].c_str(), width, height, false );
			if( data )
			{
				glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
				texture::destroyImageData( data );
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				texture::destroyImageData( data );
			}
		}
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
	}
};

typedef std::unique_ptr<CubeMap> CubeMap_ptr;
