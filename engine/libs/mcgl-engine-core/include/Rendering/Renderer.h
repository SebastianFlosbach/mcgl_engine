#pragma once

#include <sstream>

#include <glm/glm.hpp>

#include <Logging/ILogger.h>
#include "Rendering/Shader/IShader.h"
#include "Camera.h"
#include "Window.h"


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

	void draw( const world::mesh::IMesh& mesh, shader::IShader& shader, const Camera& camera ) {
		shader.setUniformMat4f( "projection", projection_ );
		mesh.draw( shader, camera );
	}

private:
	const logging::ILogger& logger_;

	IWindow_ptr pWindow_;
	Camera_ptr pCamera_;
	glm::mat4 projection_;

};

typedef std::unique_ptr<Renderer> Renderer_ptr;


}
