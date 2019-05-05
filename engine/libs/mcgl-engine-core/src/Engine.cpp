#include "Engine.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <future>

#include "Helper/OpenGLDebug.h"
#include "Eventing/KeyEventHandler.h"
#include "Eventing/MouseEventHandler.h"

#include "Coordinates/ChunkCoordinates.h"
#include "Coordinates/WorldCoordinates.h"


Engine::Engine( const ILogger& logger ) : 
	logger_( logger ),
	pBlockLibrary_( new chunk::block::BlockLibrary() ),
	pChunks_( new chunk::ChunkCollection() ),
	pWorld_( new world::World() ),
	pChunkMeshBuilder_( new chunk::builder::ThreadedChunkMeshBuilder( 4 ) ) { 
	
	if( isRunning_.exchange( true ) ) {
		return;
	}

	pChunkMeshBuilder_->setBlockLibrary( pBlockLibrary_ );
	pChunkMeshBuilder_->registerCallback( chunk::builder::CHUNK_MESH_BUILDER_CALLBACK( [this]( const coordinates::ChunkCoordinates& position, mesh::Mesh* mesh ) {
		addMesh( position.toWorldCoordinates(), mesh );
	} ) );

	pChunks_->registerCollectionChangedCallback( chunk::CHUNK_COLLECTION_CHANGED_CALLBACK( 
		[this]( const chunk::ChunkCollectionChangedEventType& type, const coordinates::ChunkCoordinates& position ) {
			switch ( type ) {
				case chunk::ChunkCollectionChangedEventType::ChunkAdded:
					pChunkMeshBuilder_->build( position, *pChunks_ );
					break;
				case chunk::ChunkCollectionChangedEventType::ChunkRemoved:
					pWorld_->removeMesh( position.toWorldCoordinates() );
					break;
				default:
					break;
			}
		} ) 
	);

	workerQueue_.registerCallback( std::bind( &Engine::doAction, this, std::placeholders::_1 ) );

	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::EngineInitAction() ) );
}

void Engine::addMesh( const coordinates::WorldCoordinates& position, mesh::Mesh* mesh ) {
	auto mesh_ptr = std::unique_ptr<mesh::Mesh>( mesh );

	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::AddMeshAction( position, std::move( mesh_ptr ) ) ) );
}

void Engine::doAddMesh( action::AddMeshAction* data ) {
	data->pMesh_->setupMesh();
	pWorld_->addMesh( data->position_, std::move( data->pMesh_ ) );
}

void Engine::doAction( action::Action* action ) {
	switch( action->type() ) {
	case action::ActionType::AddChunkAction:
		doAddChunk( static_cast<action::AddChunkAction*>( action ) );
		break;
	case action::ActionType::AddMeshAction:
		doAddMesh( static_cast<action::AddMeshAction*>( action ) );
		break;
	case action::ActionType::CloseWindowAction:
		doCloseWindow();
		break;
	case action::ActionType::CreateCameraAction:
		doCreateCamera( static_cast<action::CreateCameraAction*>( action ) );
		break;
	case action::ActionType::CreateWindowAction:
		doCreateWindow( static_cast<action::CreateWindowAction*>( action ) );
		break;
	case action::ActionType::DrawAction:
		doDraw();
		break;
	case action::ActionType::EngineInitAction:
		doEngine();
		break;
	case action::ActionType::MoveCameraAction:
		doMoveCamera( static_cast<action::MoveCameraAction*>( action ) );
		break;
	case action::ActionType::RegisterBlockTypeAction:
		doRegisterBlockType( static_cast<action::RegisterBlockTypeAction*>( action ) );
		break;
	case action::ActionType::RegisterKeyEventCallbackAction:
		doRegisterKeyEventCallback( static_cast<action::RegisterKeyEventCallbackAction*>( action ) );
		break;
	case action::ActionType::RegisterMouseEventCallbackAction:
		doRegisterMouseEventCallback( static_cast<action::RegisterMouseEventCallbackAction*>( action ) );
		break;
	case action::ActionType::RegisterStatusEventCallbackAction:
		doRegisterStatusEventCallback( static_cast<action::RegisterStatusEventCallbackAction*>( action ) );
		break;
	case action::ActionType::RemoveChunkAction:
		doRemoveChunk( static_cast<action::RemoveChunkAction*>( action ) );
		break;
	case action::ActionType::RotateCameraAction:
		doRotateCamera( static_cast<action::RotateCameraAction*>( action ) );
		break;
	case action::ActionType::RunAction:
		doDraw();
		break;
	case action::ActionType::SetShaderAction:
		doSetShader( static_cast<action::SetShaderAction*>( action ) );
		break;
	case action::ActionType::SetTexturesAction:
		doSetTextures( static_cast<action::SetTexturesAction*>( action ) );
		break;
	case action::ActionType::StopAction:
		doStop();
		break;
	default:
		break;
	}
}

void Engine::createWindow( UNUM32 width, UNUM32 height, const std::string& title ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::CreateWindowAction( width, height, title ) ) );
}

void Engine::closeWindow() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::CloseWindowAction() ) );
}

void Engine::registerBlockType( const chunk::block::Block& block ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RegisterBlockTypeAction( block ) ) );
}

void Engine::registerKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RegisterKeyEventCallbackAction( callback ) ) );
}

void Engine::registerMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RegisterMouseEventCallbackAction( callback ) ) );
}

void Engine::registerStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RegisterStatusEventCallbackAction( callback ) ) );
}

void Engine::addChunk( const chunk::Chunk& chunk ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::AddChunkAction( std::make_unique<chunk::Chunk>( chunk ) ) ) );
}

void Engine::removeChunk( UNUM32 x, UNUM32 z ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RemoveChunkAction( x, z ) ) );
}

void Engine::setTextures( const std::string& texturePath, NUM32 size, NUM32 textureCount ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::SetTexturesAction( texturePath, size, textureCount ) ) );
}

void Engine::setShader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::SetShaderAction( vertexShaderPath, fragmentShaderPath ) ) );
}

UNUM32 Engine::createCamera( double x, double y, double z, double pitch, double yaw, double roll ) {
	std::promise<void> promise{};
	auto future = promise.get_future();

	UNUM32 cameraId_ = 0;

	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::CreateCameraAction( x, y, z, pitch, yaw, roll, [&promise, &cameraId_]( const UNUM32 cameraId ) {
		cameraId_ = cameraId;
		promise.set_value();
	} ) ) );

	future.wait();

	return cameraId_;
}

void Engine::moveCamera( UNUM32 cameraId, double dx, double dy, double dz ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::MoveCameraAction( cameraId, dx, dy, dz ) ) );
}

void Engine::rotateCamera( UNUM32 cameraId, double pitch, double yaw, double roll ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RotateCameraAction( cameraId, pitch, yaw, roll ) ) );
}

void Engine::run() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RunAction() ) );
}

void Engine::stop() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::StopAction() ) );
}

void Engine::doEngine() {
	info( logger_, "Initialize engine" );
	if( !glfwInit() ) {
		throw std::runtime_error( "Could not initialize GLFW!" );
	}
	glfwSetErrorCallback( errorCallback );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	pRenderer_ = std::make_unique<Renderer>();
}

void Engine::doCreateWindow( action::CreateWindowAction* data ) {
	info( logger_, "createWindow()" );

	Window::open( data->width_, data->height_, data->title_ );
	Window::registerResizeCallback( MCGL_WINDOW_RESIZE_CALLBACK( [this]( NUM32 width, NUM32 height ) {
		pRenderer_->setProjectionMatrix( glm::perspective( glm::radians( 45.0f ), (float)width / (float)height, 0.1f, 500.0f ) );
	} ) );

	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glfwSetInputMode( Window::get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	glEnable( GL_DEPTH_TEST );
}

void Engine::doCloseWindow() {
	Window::close();
}

void Engine::doRegisterBlockType( action::RegisterBlockTypeAction* data ) {
	info( logger_, "addBlockType()" );

	pBlockLibrary_->registerBlock( data->block_ );
}

void Engine::doRegisterKeyEventCallback( action::RegisterKeyEventCallbackAction* data ) {
	info( logger_, "registerKeyEventCallback" );

	KeyEventHandler::registerCallback( Window::get(), data->callback_ );
}

void Engine::doRegisterMouseEventCallback( action::RegisterMouseEventCallbackAction* data ) {
	info( logger_, "registerMouseEventCallback" );

	MouseEventHandler::registerCallback( Window::get(), data->callback_ );
}

void Engine::doRegisterStatusEventCallback( action::RegisterStatusEventCallbackAction* data ) {
	info( logger_, "registerStatusEventCallback" );

	statusCallback_ = data->callback_;
}

void Engine::doAddChunk( action::AddChunkAction* data ) {
	pChunks_->addChunk( std::move( data->pChunk_ ) );
}

void Engine::doRemoveChunk( action::RemoveChunkAction* data ) {
	pChunks_->removeChunk( { data->x_, data->z_ } );
}

void Engine::doSetTextures( action::SetTexturesAction* data ) {
	texture::TextureAtlas textureAtlas( data->texturePath_, data->size_, data->textureCount_ );

	pRenderer_->setTextures( std::move( textureAtlas ) );
	pChunkMeshBuilder_->setTextureAtlas( pRenderer_->getTextureAtlas() );
}

void Engine::doSetShader( action::SetShaderAction* data ) {
	Shader shader = Shader();
	shader.addVertexShader( data->vertexShaderPath_ );
	shader.addFragmentShader( data->fragmentShaderPath_ );
	shader.compile();

	pRenderer_->setShader( std::move( shader ) );
}

void Engine::doCreateCamera( action::CreateCameraAction* data ) {
	camera_ = Camera( data->x_, data->y_, data->z_, data->pitch_, data->yaw_, data->roll_ );
	data->returnCallback_( 1 );
}

void Engine::doMoveCamera( action::MoveCameraAction* data ) {
	camera_.move( data->dx_, data->dy_, data->dz_ );
}

void Engine::doRotateCamera( action::RotateCameraAction* data ) {
	camera_.rotate( data->pitch_, data->yaw_, data->roll_ );
}

void Engine::doDraw() {
	// Generate delta time
	float currentFrame = glfwGetTime();
	deltaTime_ = currentFrame - lastFrame_;
	lastFrame_ = currentFrame;

	// Clear current frame
	glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	pRenderer_->setViewMatrix( camera_.getView() );

	pWorld_->draw( *pRenderer_ );

	glfwSwapBuffers( Window::get() );
	glfwPollEvents();
	KeyEventHandler::pollEvents();

	if( isRunning_ ) {
		workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::DrawAction() ) );
	}
	else {
		if( statusCallback_ ) {
			statusCallback_( { StatusEventType::Stopped } );
		}
	}
}

void Engine::doStop() {
	isRunning_ = false;
}
