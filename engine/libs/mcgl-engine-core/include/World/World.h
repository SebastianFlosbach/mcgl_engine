#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "Mesh/Mesh.h"
#include "Renderer/Renderer.h"


namespace world {

	/**
		A collection of meshes with their world space coordinates
	*/
	class World {
	public:
		World() = default;

		World( const World& other ) = delete;
		World& operator=( const World& other ) = delete;

		World( World&& other ) noexcept;
		World& operator=( World&& other ) noexcept;

		/**
			Add a mesh to the world.
			\param position Position of the mesh inside the world
			\param mesh Mesh to add to the world
		*/
		void addMesh( const glm::vec3& position, mesh::Mesh_ptr&& mesh );

		/**
			Remove a mesh from the world.
			\param position The mesh at this position will be removed
		*/
		void removeMesh( const glm::vec3& position );

		/**
			Draw all meshes at their positions.
			\param renderer Renderer to draw with
		*/
		void draw( Renderer& renderer );
		
	private:
		std::unordered_map<glm::vec3, mesh::Mesh_ptr> meshes_;
		
	};

	typedef std::unique_ptr<World> World_ptr;

}