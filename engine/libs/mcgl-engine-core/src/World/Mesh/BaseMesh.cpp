#include "World/Mesh/BaseMesh.h"

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

BaseMesh::BaseMesh( const std::vector<VertexCT>& vertices, const std::vector<UNUM32>& indices ) : vertices_( vertices ), indices_( indices ) {

}

BaseMesh::BaseMesh( std::vector<VertexCT>&& vertices, std::vector<UNUM32>&& indices ) : vertices_( std::move( vertices ) ), indices_( std::move( indices ) ) {

}


}
}
