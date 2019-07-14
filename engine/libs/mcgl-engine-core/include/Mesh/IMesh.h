#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Camera.h"
#include "Rendering/Shader/IShader.h"


namespace mesh {


class IMesh {
public:
	virtual ~IMesh() = default;

	virtual void draw( rendering::shader::IShader& shader, const Camera& camera ) const = 0;
	virtual void bind() = 0;
	virtual void unbind() = 0;

	virtual const glm::mat4& getModelMatrix() const = 0;
};

typedef std::unique_ptr<IMesh> IMesh_ptr;


}
