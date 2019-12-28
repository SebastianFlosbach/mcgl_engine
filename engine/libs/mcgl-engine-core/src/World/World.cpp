#include "World/World.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>


namespace world {


void World::addMesh( world::mesh::IMesh_ptr&& mesh ) {
	auto it = meshes_.find( mesh.get() );
	
	if( it != meshes_.end() ) {
		std::stringstream msg;
		msg << __FUNCTION__ << ": Tried adding existing model [" << static_cast<const void*>(mesh.get()) << "]";
		warn( logger_, msg.str() );
		return;
	}
	else {
		std::stringstream msg;
		msg << __FUNCTION__ << ": Adding new model [" << static_cast<const void*>(mesh.get()) << "]";
		debug( logger_, msg.str() );
		meshes_.insert( { mesh.get(), std::move( mesh ) } );
	}

}

void World::removeMesh( world::mesh::IMesh_ptr&& mesh ) {
	std::stringstream msg;
	msg << __FUNCTION__ << ": Removing model [" << static_cast<const void*>(mesh.get()) << "]";
	debug( logger_, msg.str() );
	meshes_.erase( mesh.get() );
}

void World::removeMesh( const coordinates::WorldCoordinates& coordinates ) {
	for( auto it = meshes_.begin(); it != meshes_.end(); it++ ) {
		float x = it->second->getModelMatrix()[0][3];
		float y = it->second->getModelMatrix()[1][3];
		float z = it->second->getModelMatrix()[2][3];

		if( coordinates.x_ == x &&
			coordinates.y_ == y &&
			coordinates.z_ == z ) {

			std::stringstream msg;
			msg << __FUNCTION__ << ": Removing model [" << static_cast<const void*>(&it->second) << "]";
			debug( logger_, msg.str() );

			meshes_.erase( it );
			break;
		}
	}
}

void World::draw( rendering::Renderer& renderer ) {
	for( auto it = meshes_.begin(); it != meshes_.end(); it++ ) {
		renderer.draw(*it->second );
	}
}


}