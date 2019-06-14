#pragma once

#include <sstream>

#include <glm/glm.hpp>

#include <Logging/ILogger.h>
#include "Texture/TextureAtlas.h"
#include "Rendering/Shader/IShader.h"
#include "Window.h"


namespace rendering {


enum class ShaderType {
	Chunk,
	Skybox
};


class Renderer {
public:
	Renderer( const logging::ILogger& logger ) : logger_( logger ) {

	}

	Renderer( const logging::ILogger& logger, texture::TextureAtlas&& textureAtlas ) :
		logger_( logger ),
		pTextureAtlas_( std::make_shared<texture::TextureAtlas>( std::move( textureAtlas ) ) )
	{}

	~Renderer() = default;

	void setShader( shader::IShader_ptr&& shader, ShaderType type ) {
		switch( type )
		{
		case ShaderType::Chunk:
			pChunkShader_ = std::move( shader );
			break;
		case ShaderType::Skybox:
			pSkyboxShader_ =  std::move( shader );
			break;
		default:
			break;
		}
		
	}

	shader::IShader& getShader( ShaderType type ) const {
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

	void setModelMatrix( const glm::mat4& model, ShaderType type ) {
		switch( type ) {
		case ShaderType::Chunk:
			pChunkShader_->setUniformMat4f( "model", model );
			break;
		case ShaderType::Skybox:
			pSkyboxShader_->setUniformMat4f( "model", model );
			break;
		default:
			break;
		}
	}

	void setViewMatrix( const glm::mat4& view, ShaderType type ) {
		useShader( type );
		switch( type ) {
		case ShaderType::Chunk:
			pChunkShader_->setUniformMat4f( "view", view );
			break;
		case ShaderType::Skybox:
			pSkyboxShader_->setUniformMat4f( "view", view );
			break;
		default:
			break;
		}
	}

	void setProjectionMatrix( const glm::mat4& projection, ShaderType type ) {
		useShader( type );
		switch( type ) {
		case ShaderType::Chunk:
			pChunkShader_->setUniformMat4f( "projection", projection );
			break;
		case ShaderType::Skybox:
			pSkyboxShader_->setUniformMat4f( "projection", projection );
			break;
		default:
			break;
		}
	}

	void useShader( ShaderType type ) {
		switch( type )
		{
		case ShaderType::Chunk:
			pChunkShader_->use();
			pTextureAtlas_->bind();
			break;
		case ShaderType::Skybox:
			pSkyboxShader_->use();
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

	shader::IShader_ptr pChunkShader_;
	shader::IShader_ptr pSkyboxShader_;

};

typedef std::unique_ptr<Renderer> Renderer_ptr;


}
