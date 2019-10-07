#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "Logging/ILogger.h"
#include "World/Mesh/IMesh.h"
#include "Rendering/Renderer.h"


namespace world {

/**
	A collection of meshes
*/
class World {
public:
	World( const logging::ILogger& logger ) : logger_( logger ) {}

	~World() = default;

	World( const World& other ) = delete;
	World& operator=( const World& other ) = delete;

	World( World&& other ) = delete;
	World& operator=( World&& other ) = delete;

	/**
		Add a mesh to the world.
		\param mesh Mesh to add to the world
	*/
	void addMesh( world::mesh::IMesh_ptr&& model );

	/**
		Remove a mesh from the world.
		\param position The mesh to remove
	*/
	void removeMesh( world::mesh::IMesh_ptr&& model );

	/**
		Draw all models
		\param renderer Renderer to draw with
	*/
	void draw( rendering::Renderer& renderer );

private:
	const logging::ILogger& logger_;

	std::unordered_map<world::mesh::IMesh*, world::mesh::IMesh_ptr> meshes_;

};

typedef std::unique_ptr<World> World_ptr;


}
