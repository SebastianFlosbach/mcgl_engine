#include "Mesh/BaseMesh.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace world {
namespace mesh {


void BaseMesh::bind() {
	glBindVertexArray( hVertexArray_ );
}

void BaseMesh::unbind() {
	glBindVertexArray( 0 );
}

const glm::mat4& BaseMesh::getModelMatrix() const {
	return model_;
}


}
}
