#include "Engine.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Helper/OpenGLDebug.h"
#include "Eventing/KeyEventHandler.h"
#include "Eventing/MouseEventHandler.h"

Engine::Engine( const ILogger& logger ) : logger_( logger ) {
	info( logger_, "Initialize engine" );
	if ( !glfwInit() ) {
		throw std::runtime_error( "Could not initialize GLFW!" );
	}
	glfwSetErrorCallback( errorCallback );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	renderer_ = std::make_unique<Renderer>();
}

void Engine::createWindow( unsigned int width, unsigned int height, const std::string& title ) {
	info( logger_, "createWindow()" );

	window_ = Window( width, height, title );

	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}

void Engine::addBlockType( const world::block::Block& block, unsigned int id ) {
	info( logger_, "addBlockType()" );

	blockLibrary_.addBlock( block, id );
}

void Engine::registerKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	info( logger_, "registerKeyEventCallback" );

	KeyEventHandler::registerCallback( window_.get(), callback );
}

void Engine::registerMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {
	info( logger_, "registerMouseEventCallback" );

	MouseEventHandler::registerCallback( window_.get(), callback );
}

void Engine::addChunk( unsigned int x, unsigned int z, const world::chunk::Chunk& chunk ) {
	world_.addChunk( x, z, chunk );
}

void Engine::setTextures( texture::TextureAtlas&& textureAtlas ) {
	renderer_->setTextures( std::move( textureAtlas ) );
}

void Engine::setShader( Shader&& shader ) {
	renderer_->setShader( std::move( shader ) );
}

unsigned int createCamera( unsigned int x, unsigned int y, unsigned int z, double pitch, double yaw, double roll = 0.0 ) {
	
}

void Engine::run() {
	info( logger_, "run()" );

	glViewport( 0, 0, window_.width(), window_.height() );

	glfwSetInputMode( window_.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	glEnable( GL_DEPTH_TEST );


	glm::mat4 model( 1.0f );
	model = glm::scale( model, { 0.2f, 0.2f, 0.2f } );

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	auto mesh = world_.generateMesh( blockLibrary_, renderer_->getTextureAtlas() );

	while ( !glfwWindowShouldClose( window_.get() ) ) {
		// Rendering
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		for ( auto& chunkMesh : mesh ) {
			chunkMesh->draw( *renderer_ );
		}

		glfwSwapBuffers( window_.get() );
		glfwPollEvents();
	}
}