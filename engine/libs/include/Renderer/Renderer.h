#pragma once

#include "../Texture/TextureAtlas.h"
#include "../Shader.h"


class Renderer {
public:
	Renderer() = default;
	Renderer( Shader&& shader, texture::TextureAtlas&& textureAtlas ) : pShader_( std::make_unique<Shader>( std::move( shader ) ) ), pTextureAtlas_( std::make_unique<texture::TextureAtlas>( std::move( textureAtlas ) ) ) {}

	void setShader( Shader&& shader ) {
		pShader_ = std::make_unique<Shader>( std::move( shader ) );
	}

	const Shader& getShader() const {
		return *pShader_;
	}

	void setTextures( texture::TextureAtlas&& textureAtlas ) {
		pTextureAtlas_ = std::make_unique<texture::TextureAtlas>( std::move( textureAtlas ) );
	}

	const texture::TextureAtlas& getTextureAtlas() const {
		return *pTextureAtlas_;
	}

	void bindTexture() {
		pTextureAtlas_->bind();
	}

private:
	std::unique_ptr<texture::TextureAtlas> pTextureAtlas_;
	std::unique_ptr<Shader> pShader_;

};
