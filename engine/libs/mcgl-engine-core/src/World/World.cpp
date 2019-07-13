#include "World/World.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>


namespace world {


void World::addModel( const world::objects::Model_sptr& model ) {
	auto it = models_.find( model.get() );
	
	if( it != models_.end() ) {
		std::stringstream msg;
		msg << __FUNCTION__ << ": Tried adding existing model [" << static_cast<const void*>(model.get()) << "]";
		warn( logger_, msg.str() );
		return;
	}
	else {
		std::stringstream msg;
		msg << __FUNCTION__ << ": Adding new model [" << static_cast<const void*>(model.get()) << "]";
		debug( logger_, msg.str() );
		models_.insert( { model.get(), model } );
	}

}

void World::removeModel( const world::objects::Model_sptr& model ) {
	std::stringstream msg;
	msg << __FUNCTION__ << ": Removing model [" << static_cast<const void*>(model.get()) << "]";
	debug( logger_, msg.str() );
	models_.erase( model.get() );
}

void World::draw( rendering::Renderer& renderer ) {

}


}