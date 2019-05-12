#include "World/World.h"

#include <sstream>

namespace world {


void World::addMesh( const coordinates::WorldCoordinates& position, mesh::Mesh_ptr&& mesh ) {
	auto it = meshes_.find( position );
	
	if( it != meshes_.end() ) {
		std::stringstream newPointerString;
		newPointerString << static_cast<const void*>(mesh.get());
		std::stringstream oldPointerString;
		oldPointerString << static_cast<const void*>(it->second.get());
		debug( logger_, std::string( __FUNCTION__ ) + std::string( ": Updating existing mesh " ) + oldPointerString.str() + std::string( " with new mesh " ) + newPointerString.str() + std::string( " at position " ) + position.to_string() );
		it->second->update( std::move( mesh ) );
	}
	else {
		std::stringstream ss;
		ss << static_cast<const void*>(mesh.get());
		debug( logger_, std::string( __FUNCTION__ ) + std::string( ": Adding new mesh " ) + ss.str() + std::string( " at position " ) + position.to_string() );
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