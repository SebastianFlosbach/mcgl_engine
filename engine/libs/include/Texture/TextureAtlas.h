#pragma once

#include <string>
#include <vector>

#include "Texture.h"

namespace texture {


class TextureAtlas {
public:
	TextureAtlas( const std::string& path, unsigned int size, unsigned int textureCount ) : texture_( Texture( path ) ), size_( size ), textureCount_( textureCount ) {
		if ( texture_.width() % size_ != 0 || texture_.height() % size_ != 0 || texture_.width() % size_ != texture_.height() % size_ ) {
			throw std::runtime_error( "TextureAtlas: Could not extract tiles from image" );
		}

		rows_ = texture_.height() / size_;
		columns_ = texture_.width() / size_;

		textureSizeX_ = 1.0f / (float)columns_;
		textureSizeY_ = 1.0f / (float)rows_;
	}

	std::vector<float> getTextureCoords( unsigned int id ) const {
		auto row = id / columns_;
		auto column = id % columns_;

		if ( row >= rows_ ) {
			throw std::invalid_argument( "TextureAtlas::getTextureCoords: id out of range" );
		}

		return {
			column * textureSizeX_,			1.0f - (row + 1) * textureSizeY_,
			(column + 1) * textureSizeX_,	1.0f - (row + 1) * textureSizeY_,
			(column + 1) * textureSizeX_,	1.0f - row * textureSizeY_,
			column * textureSizeX_,			1.0f - row * textureSizeY_,
		};
	}

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


}