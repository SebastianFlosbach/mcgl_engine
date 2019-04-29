#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "Mesh/Mesh.h"
#include "Renderer/Renderer.h"


namespace world {

	/**
		A collection of meshes
	*/
	class World {
	public:
		World() = default;

		World( const World& other ) = delete;
		World& operator=( const World& other ) = delete;

		World( World&& other ) noexcept;
		World& operator=( World&& other ) noexcept;

		void draw( Renderer& renderer );
		
	private:
		std::unordered_map<glm::vec3, mesh::Mesh_ptr> meshes_;
		
	};

	typedef std::unique_ptr<World> World_ptr;

}