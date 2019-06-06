#pragma once
#include "glad/glad.h"

#include <vector>

#include "Rendering/Renderer.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

struct CubeMap {
public:
	CubeMap( const std::vector<std::string>& faces ) {
		hCubeMap_ = loadCubemap( faces );
	}

	void bind() {
		glBindTexture( GL_TEXTURE_CUBE_MAP, hCubeMap_ );
	}

private:
	UNUM32 hCubeMap_;

	UNUM32 loadCubemap( const std::vector<std::string>& faces ) {
		UNUM32 textureID;
		glGenTextures( 1, &textureID );
		glBindTexture( GL_TEXTURE_CUBE_MAP, textureID );

		int width, height, nrChannels;
		for ( unsigned int i = 0; i < faces.size(); i++ ) {
			unsigned char *data = stbi_load( faces[i].c_str(), &width, &height, &nrChannels, 0 );
			if ( data ) {
				glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
							  0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
			} else {
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			}
			stbi_image_free( data );
		}
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );

		return textureID;
	}
};

typedef std::unique_ptr<CubeMap> CubeMap_ptr;
