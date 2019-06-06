#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "Logging/ILogger.h"
#include "Mesh/Mesh.h"
#include "Rendering/Renderer.h"
#include "Coordinates/WorldCoordinates.h"
#include "CubeMap.h"


namespace world {

	/**
		A collection of meshes with their world space coordinates
	*/
	class World {
	public:
		World( const ILogger& logger ) : logger_( logger ) {}

		~World() = default;

		World( const World& other ) = delete;
		World& operator=( const World& other ) = delete;

		World( World&& other ) = delete;
		World& operator=( World&& other ) = delete;

		/**
			Add a mesh to the world.
			\param position Position of the mesh inside the world
			\param mesh Mesh to add to the world
		*/
		void addMesh( const coordinates::WorldCoordinates& position, mesh::Mesh_ptr&& mesh );

		/**
			Remove a mesh from the world.
			\param position The mesh at this position will be removed
		*/
		void removeMesh( const coordinates::WorldCoordinates& position );

		void setSkybox( 
			const std::string& right,
			const std::string& left,
			const std::string& top,
			const std::string& bottom,
			const std::string& front,
			const std::string& back
		);

		/**
			Draw all meshes at their positions.
			\param renderer Renderer to draw with
		*/
		void draw( Renderer& renderer );
		
	private:
		const ILogger& logger_;

		std::unordered_map<coordinates::WorldCoordinates, mesh::Mesh_ptr> meshes_;
		CubeMap_ptr pSkybox_;
		
	};

	typedef std::unique_ptr<World> World_ptr;

}
