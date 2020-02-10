#include "Texture/TextureLibrary.h"


namespace texture {


	void TextureLibrary::addTexture( const std::string& name, Texture&& texture ) {
		auto it = textures_.find( name );

		if( it != textures_.end() ) {
			return;
		}

		textures_.insert( { name, std::move( texture ) } );
	}

	void TextureLibrary::addTextureAtlas( const std::string& name, TextureAtlas&& textureAtlas ) {
		auto it = textureAtlases_.find( name );

		if( it != textureAtlases_.end() ) {
			return;
		}

		textureAtlases_.insert( { name, std::move( textureAtlas ) } );
	}

	texture::Texture* TextureLibrary::getTexture( const std::string& name ) {
		auto textureIterator = textures_.find( name );

		if( textureIterator != textures_.end() ) {
			return &textureIterator->second;
		} else {
			return nullptr;
		}
	}

	texture::TextureAtlas* TextureLibrary::getTextureAtlas( const std::string& name ) {
		auto textureIterator = textureAtlases_.find( name );

		if( textureIterator != textureAtlases_.end() ) {
			return &textureIterator->second;
		} else {
			return nullptr;
		}
	}

	void TextureLibrary::bindTexture( const std::string& name ) {
		auto textureIterator = textures_.find( name );

		if( textureIterator != textures_.end() ) {
			textureIterator->second.bind();
			return;
		}

		auto atlasIterator = textureAtlases_.find( name );

		if( atlasIterator != textureAtlases_.end() ) {
			atlasIterator->second.bind();
			return;
		}
	}
}
