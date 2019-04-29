#include "World/World.h"


namespace world {


World::World( World&& other ) : meshes_( std::move( other.meshes_ ) ) {}

World& World::operator=( World&& other ) {
	return std::move( other );
}

void World::draw( Renderer& renderer ) {
	for ( auto& meshData : meshes_ ) {

		glm::mat4 model = glm::mat4( 1.0f );
		model = glm::translate( model, meshData.first );

		renderer.setModelMatrix( model );

		meshData.second->draw( renderer );
	}
}


}