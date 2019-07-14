#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "Logging/ILogger.h"
#include "Rendering/Renderer.h"


namespace world {

	/**
		A collection of models
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
			Add a model to the world.
			\param mesh Model to add to the world
		*/
		void addModel( const world::objects::Model_sptr& model );

		/**
			Remove a model from the world.
			\param position The Model to remove
		*/
		void removeModel( const world::objects::Model_sptr& model );

		/**
			Draw all models
			\param renderer Renderer to draw with
		*/
		void draw( rendering::Renderer& renderer );
		
	private:
		const logging::ILogger& logger_;

		std::unordered_map<world::objects::Model*, world::objects::Model_sptr> models_;
		
	};

	typedef std::unique_ptr<World> World_ptr;

}
