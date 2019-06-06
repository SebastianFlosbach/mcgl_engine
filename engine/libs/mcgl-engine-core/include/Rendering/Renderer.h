#pragma once

#include <sstream>

#include <glm/glm.hpp>

#include <Logging/ILogger.h>
#include "Texture/TextureAtlas.h"
#include "Shader.h"
#include "Window.h"


class Renderer {
public:
	Renderer( const logging::ILogger& logger ) : logger_( logger ) {

	}

	Renderer( const logging::ILogger& logger, texture::TextureAtlas&& textureAtlas ) :
		logger_( logger ),
		pTextureAtlas_( std::make_shared<texture::TextureAtlas>( std::move( textureAtlas ) ) )
	{}

	~Renderer() = default;

	void setShader( Shader&& shader, ShaderType type ) {
		switch( type )
		{
		case ShaderType::Chunk:
			pChunkShader_ = std::make_unique<Shader>( std::move( shader ) );
			break;
		case ShaderType::Skybox:
			pSkyboxShader_ = std::make_unique<Shader>( std::move( shader ) );
			break;
		default:
			break;
		}
		
	}

	const Shader& getShader( ShaderType type ) const {
		switch( type )
		{
		case ShaderType::Chunk:
			return *pChunkShader_;
		case ShaderType::Skybox:
			return *pSkyboxShader_;
		default:
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Invalid shader type '" << std::to_string( (int)type ) << "'!";
			critical( logger_, errorMsg.str() );
			throw std::invalid_argument( errorMsg.str() );
		}
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

	void use( ShaderType type ) {
		switch( type )
		{
		case ShaderType::Chunk:
			pChunkShader_->use();
			pChunkShader_->setUniformMat4f( "model", model_ );
			pChunkShader_->setUniformMat4f( "view", view_ );
			pChunkShader_->setUniformMat4f( "projection", projection_ );
			pTextureAtlas_->bind();
			break;
		case ShaderType::Skybox:
			pSkyboxShader_->use();
			pSkyboxShader_->setUniformMat4f( "view", view_ );
			pSkyboxShader_->setUniformMat4f( "projection", projection_ );
			break;
		default:
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Invalid shader type '" << std::to_string( (int)type ) << "'!";
			critical( logger_, errorMsg.str() );
			throw std::invalid_argument( errorMsg.str() );
		}

	}

private:
	const logging::ILogger& logger_;

	texture::TextureAtlas_sptr pTextureAtlas_;

	Shader_ptr pChunkShader_;
	Shader_ptr pSkyboxShader_;

	glm::mat4 model_ = glm::mat4( 1.0f );
	glm::mat4 view_ = glm::mat4( 1.0f );
	glm::mat4 projection_ = glm::perspective( glm::radians( 45.0f ), 800.f / 600.f, 0.1f, 500.0f );
};

typedef std::unique_ptr<Renderer> Renderer_ptr;
