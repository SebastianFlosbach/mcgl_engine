#pragma once

#include <glm/glm.hpp>

#include "Texture/TextureAtlas.h"
#include "Shader.h"
#include "Window.h"


class Renderer {
public:
	Renderer() = default;
	Renderer( Shader&& shader, texture::TextureAtlas&& textureAtlas ) : 
		pShader_( std::make_unique<Shader>( std::move( shader ) ) ), 
		pTextureAtlas_( std::make_shared<texture::TextureAtlas>( std::move( textureAtlas ) ) )
	{}

	~Renderer() = default;

	void setShader( Shader&& shader ) {
		pShader_ = std::make_unique<Shader>( std::move( shader ) );
	}

	const Shader& getShader() const {
		return *pShader_;
	}

	void setTextures( texture::TextureAtlas&& textureAtlas ) {
		pTextureAtlas_ = std::make_unique<texture::TextureAtlas>( std::move( textureAtlas ) );
	}

	const texture::TextureAtlas_sptr& getTextureAtlas() const {
		return pTextureAtlas_;
	}

	void setModelMatrix( const glm::mat4& model ) {
		model_ = model;
	}

	void setViewMatrix( const glm::mat4& view ) {
		view_ = view;
	}

	void setProjectionMatrix( const glm::mat4& projection ) {
		projection_ = projection;
	}

	void use() {
		pShader_->use();
		pShader_->setUniformMat4f( "model", model_ );
		pShader_->setUniformMat4f( "view", view_ );
		pShader_->setUniformMat4f( "projection", projection_ );

		pTextureAtlas_->bind();
	}

private:
	texture::TextureAtlas_sptr pTextureAtlas_;

	Shader_ptr pShader_;

	glm::mat4 model_ = glm::mat4( 1.0f );
	glm::mat4 view_ = glm::mat4( 1.0f );
	glm::mat4 projection_ = glm::perspective( glm::radians( 45.0f ), 800.f / 600.f, 0.1f, 500.0f );
};

typedef std::unique_ptr<Renderer> Renderer_ptr;
