#include "World/World.h"


namespace world {


void World::addMesh( const coordinates::WorldCoordinates& position, mesh::Mesh_ptr&& mesh ) {
	auto it = meshes_.find( position );
	
	if( it != meshes_.end() ) {
		it->second->update( std::move( mesh ) );
	}
	else {
		meshes_.insert( { position, std::move( mesh ) } );
	}

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