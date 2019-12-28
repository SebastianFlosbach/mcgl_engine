#pragma once

#include <sstream>
#include <glm/glm.hpp>
#include <Logging/ILogger.h>
#include <map>

#include "Rendering/Shader/IShader.h"
#include "Camera.h"
#include "Window.h"
#include "World/Mesh/IMesh.h"

namespace rendering {


class Renderer {
public:
	Renderer( const logging::ILogger& logger, IWindow_ptr&& pWindow ) : logger_( logger ), pWindow_( std::move( pWindow ) ) {
		projection_ = glm::perspective( glm::radians( 45.0f ), (float)pWindow_->width() / (float)pWindow_->height(), 0.1f, 500.0f );
	}

	~Renderer() = default;

	void setProjection( const glm::mat4& projection ) {
		projection_ = projection;
	}

	const IWindow& getWindow() const {
		return *pWindow_.get();
	}

	void setCamera( Camera_ptr&& camera ) {
		pCamera_ = std::move( camera );
	}

	Camera* getCamera() {
		return pCamera_.get();
	}

	void addShader( shader::IShader* shader, const std::string& name ){
		auto it = shaders_.find(name);

		if( it != shaders_.end() ) {
			error( logger_, "Failed to add shader to renderer. Shader already exists!" );
			return;
		}

		shaders_.insert( { name, shader::IShader_ptr( shader ) } );
	}

	void setShader( const std::string& name ) {
		auto it = shaders_.find( name );

		if( it == shaders_.end() ) {
			error( logger_, "Failed to set shader. Shader does not exist!" );
			return;
		}

		currentShader_ = name;
	}

	void draw( const world::mesh::IMesh& mesh ) {
		shaders_[currentShader_]->setUniformMat4f( "projection", projection_ );
		mesh.draw( *shaders_[currentShader_], *pCamera_ );
	}

private:
	const logging::ILogger& logger_;

	std::map<std::string, shader::IShader_ptr> shaders_;
	IWindow_ptr pWindow_;
	Camera_ptr pCamera_;
	glm::mat4 projection_;

	std::string currentShader_;

};

typedef std::unique_ptr<Renderer> Renderer_ptr;


}
