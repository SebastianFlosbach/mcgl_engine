#pragma once

#include <string>
#include <vector>

#include "Texture.h"

namespace texture {


class TextureAtlas {
public:
	TextureAtlas( const std::string& path, unsigned int size, unsigned int textureCount );

	std::vector<float> getTextureCoords( unsigned int id ) const;

	void bind() const {
		texture_.bind();
	}

private:
	Texture texture_;

	// Size in pixels of a single tile
	unsigned int size_;

	// Size of a tile in texture coordinates e.g. from 0.0f to 1.0f
	float textureSizeX_;
	float textureSizeY_;

	// Number of textures in this atlas
	unsigned int textureCount_;

	unsigned int rows_;
	unsigned int columns_;

};

typedef std::unique_ptr<TextureAtlas> TextureAtlas_ptr;
typedef std::shared_ptr<TextureAtlas> TextureAtlas_sptr;

}