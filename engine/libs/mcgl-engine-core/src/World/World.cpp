#include "World/World.h"


namespace world {


//World::World( World&& other ) noexcept : meshes_( std::move( other.meshes_ ) ) {}
//
//World& World::operator=( World&& other ) noexcept {
//	return std::move( other );
//}

void World::addMesh( const coordinates::WorldCoordinates& position, mesh::Mesh_ptr&& mesh ) {
	meshes_.insert( { position, std::move( mesh ) } );
}

void World::removeMesh( const coordinates::WorldCoordinates& position ) {
	meshes_.erase( position );
}

void World::draw( Renderer& renderer ) {
	for ( auto& meshData : meshes_ ) {

		glm::mat4 model = glm::mat4( 1.0f );
		model = glm::translate( model, meshData.first.toVec3() );

		renderer.setModelMatrix( model );

		meshData.second->draw( renderer );
	}
}


}