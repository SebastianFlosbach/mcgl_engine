#pragma once

#include <map>

#include "Texture/Texture.h"
#include "Texture/TextureAtlas.h"


namespace texture {


	class TextureLibrary {
	public:
		TextureLibrary() = default;

		void addTexture( const std::string& name, Texture&& texture );
		void addTextureAtlas( const std::string& name, TextureAtlas&& textureAtlas );

		void bindTexture( const std::string& name );

	private:
		std::map<std::string, Texture> textures_;
		std::map<std::string, TextureAtlas> textureAtlases_;

	};


}
