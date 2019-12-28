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
#include "Rendering/Shader/SkyboxShader.h"
#include "Rendering/Shader/ChunkShader.h"
#include "World/Mesh/IMesh.h"
#include "World/Mesh/Chunk/Builder/ThreadedChunkMeshBuilder.h"


Engine::Engine( const logging::ILogger& logger ) :
	logger_( logger ) {

	workerQueue_.registerCallback( std::bind( &Engine::doAction, this, std::placeholders::_1 ) );

	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::EngineInitAction() ) );

	workerQueue_.start();
}

Engine::~Engine() {
	std::unique_lock<std::mutex> lock( mEngine_ );
	cvDestroy_.wait( lock, [this]() { return isDestroyed_.load(); } );

	workerQueue_.stop();
	glfwTerminate();
	info( logger_, " Destroyed engine" );
}

void Engine::doAction( action::Action* action ) {
	switch( action->type() ) {
	case action::ActionType::AddChunkAction:
		doAddChunk( static_cast<action::AddChunkAction*>(action) );
		break;
	case action::ActionType::AddMeshAction:
		doAddMesh( static_cast<action::AddMeshAction*>(action) );
		break;
	case action::ActionType::CloseWindowAction:
		doCloseWindow();
		break;
	case action::ActionType::CreateCameraAction:
		doCreateCamera( static_cast<action::CreateCameraAction*>(action) );
		break;
	case action::ActionType::CreateWindowAction:
		doCreateWindow( static_cast<action::CreateWindowAction*>(action) );
		break;
	case action::ActionType::DestroyAction:
		doDestroy();
		break;
	case action::ActionType::DrawAction:
		doDraw();
		break;
	case action::ActionType::EngineInitAction:
		doEngine();
		break;
	case action::ActionType::MoveCameraAction:
		doMoveCamera( static_cast<action::MoveCameraAction*>(action) );
		break;
	case action::ActionType::RegisterBlockTypeAction:
		doRegisterBlockType( static_cast<action::RegisterBlockTypeAction*>(action) );
		break;
	case action::ActionType::RegisterKeyEventCallbackAction:
		doRegisterKeyEventCallback( static_cast<action::RegisterKeyEventCallbackAction*>(action) );
		break;
	case action::ActionType::RegisterMouseEventCallbackAction:
		doRegisterMouseEventCallback( static_cast<action::RegisterMouseEventCallbackAction*>(action) );
		break;
	case action::ActionType::RegisterStatusEventCallbackAction:
		doRegisterStatusEventCallback( static_cast<action::RegisterStatusEventCallbackAction*>(action) );
		break;
	case action::ActionType::RemoveChunkAction:
		doRemoveChunk( static_cast<action::RemoveChunkAction*>(action) );
		break;
	case action::ActionType::RotateCameraAction:
		doRotateCamera( static_cast<action::RotateCameraAction*>(action) );
		break;
	case action::ActionType::RunAction:
		doDraw();
		break;
	case action::ActionType::SetShaderAction:
		doSetShader( static_cast<action::SetShaderAction*>(action) );
		break;
	case action::ActionType::SetTextureAction:
		doSetTexture( static_cast<action::SetTextureAction*>(action) );
		break;
	case action::ActionType::StopAction:
		doStop();
		break;
	default:
		break;
	}
}

// AddMesh
void Engine::addMesh( const coordinates::WorldCoordinates& position, world::mesh::IMesh* mesh ) {
	auto mesh_ptr = std::unique_ptr<world::mesh::IMesh>( mesh );

	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::AddMeshAction( std::move( mesh_ptr ) ) ) );
}

void Engine::doAddMesh( action::AddMeshAction* data ) {
	pWorld_->addMesh( std::move( data->pMesh_ ) );
}

// CreateWindow
void Engine::createWindow( UNUM32 width, UNUM32 height, const std::string& title ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::CreateWindowAction( width, height, title ) ) );
}

void Engine::doCreateWindow( action::CreateWindowAction* data ) {
	info( logger_, "createWindow()" );

	IWindow_sptr pWindow = Window::create();

	pWindow->open( data->width_, data->height_, data->title_ );
	pWindow->registerResizeCallback( MCGL_WINDOW_RESIZE_CALLBACK( [this]( NUM32 width, NUM32 height ) {
		pRenderer_->setProjection( glm::perspective( glm::radians( 45.0f ), (float)width / (float)height, 0.1f, 500.0f ) );
	} ) );

	if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glfwSetInputMode( pWindow->get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	glEnable( GL_DEPTH_TEST );
}

// CloseWindow
void Engine::closeWindow() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::CloseWindowAction() ) );
}

void Engine::doCloseWindow() {

}

// RegisterBlockType
void Engine::registerBlockType( const world::mesh::chunk::block::Block& block ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RegisterBlockTypeAction( block ) ) );
}

// RegisterKeyEventCallback
void Engine::registerKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RegisterKeyEventCallbackAction( callback ) ) );
}

// RegisterMouseEventCallback
void Engine::registerMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RegisterMouseEventCallbackAction( callback ) ) );
}

// RegisterStatusEventCallback
void Engine::registerStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RegisterStatusEventCallbackAction( callback ) ) );
}

// AddChunk
void Engine::addChunk( const world::mesh::chunk::Chunk& chunk ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::AddChunkAction( std::make_unique<world::mesh::chunk::Chunk>( chunk ) ) ) );
}

// RemoveChunk
void Engine::removeChunk( UNUM32 x, UNUM32 z ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RemoveChunkAction( x, z ) ) );
}

// SetTexture
void Engine::setTexture( MCGLTextureType type, const std::string& path ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::SetTextureAction( type, path ) ) );
}

// SetShader
void Engine::setShader( MCGLShaderType type, const std::string& vertexShaderPath, const std::string& fragmentShaderPath ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::SetShaderAction( type, vertexShaderPath, fragmentShaderPath ) ) );
}

// CreateCamera
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

// MoveCamera
void Engine::moveCamera( double dx, double dy, double dz ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::MoveCameraAction( dx, dy, dz ) ) );
}

// RotateCamera
void Engine::rotateCamera( double pitch, double yaw, double roll ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RotateCameraAction( pitch, yaw, roll ) ) );
}

void Engine::run() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RunAction() ) );
}

void Engine::stop() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::StopAction() ) );
}

void Engine::destroy() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::DestroyAction() ), true );
}

void Engine::doDestroy() {
	pAssetManager_.reset();
	isDestroyed_ = true;
	cvDestroy_.notify_one();
}

void Engine::doEngine() {
	info( logger_, "Initialize engine" );
	if( !glfwInit() ) {
		throw std::runtime_error( "Could not initialize GLFW!" );
	}

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	pAssetManager_ = std::make_unique<AssetManager>( logger_ );

	pAssetManager_->setChunkMeshBuilder( (world::mesh::chunk::builder::IChunkMeshBuilder*)new world::mesh::chunk::builder::ThreadedChunkMeshBuilder( logger_, 4 ) );

	if( isRunning_.exchange( true ) ) {
		return;
	}

	pAssetManager_->getChunkMeshBuilder()->setBlockLibrary( pAssetManager_->getBlockLibrary() );
	pAssetManager_->getChunkMeshBuilder()->registerCallback( world::mesh::chunk::builder::CHUNK_MESH_BUILDER_CALLBACK( [this]( const coordinates::ChunkCoordinates& position, world::mesh::TexturedMesh* mesh ) {
		addMesh( position.toWorldCoordinates(), mesh );
	} ) );

	pAssetManager_->getChunkCollection()->registerCollectionChangedCallback( world::mesh::chunk::CHUNK_COLLECTION_CHANGED_CALLBACK(
		[this]( const world::mesh::chunk::ChunkCollectionChangedEventType& type, const coordinates::ChunkCoordinates& position ) {
			switch( type ) {
			case world::mesh::chunk::ChunkCollectionChangedEventType::ChunkAdded:
				pAssetManager_->getChunkMeshBuilder()->build( position, *pAssetManager_->getChunkCollection() );
				break;
			case world::mesh::chunk::ChunkCollectionChangedEventType::ChunkRemoved:
				pWorld_->removeMesh( position.toWorldCoordinates() );
				break;
			default:
				break;
			}
		} )
	);
}

void Engine::doRegisterBlockType( action::RegisterBlockTypeAction* data ) {
	info( logger_, "addBlockType()" );

	pAssetManager_->getBlockLibrary()->registerBlock( data->block_ );
}

void Engine::doRegisterKeyEventCallback( action::RegisterKeyEventCallbackAction* data ) {
	info( logger_, "registerKeyEventCallback" );

	eventing::KeyEventHandler::registerCallback( pRenderer_->getWindow().get(), data->callback_ );
}

void Engine::doRegisterMouseEventCallback( action::RegisterMouseEventCallbackAction* data ) {
	info( logger_, "registerMouseEventCallback" );

	eventing::MouseEventHandler::registerCallback( pRenderer_->getWindow().get(), data->callback_ );
}

void Engine::doRegisterStatusEventCallback( action::RegisterStatusEventCallbackAction* data ) {
	info( logger_, "registerStatusEventCallback" );

	statusCallback_ = data->callback_;
}

void Engine::doAddChunk( action::AddChunkAction* data ) {
	pAssetManager_->getChunkCollection()->addChunk( std::move( data->pChunk_ ) );
}

void Engine::doRemoveChunk( action::RemoveChunkAction* data ) {
	pAssetManager_->getChunkCollection()->removeChunk( { data->x_, data->z_ } );
}

void Engine::doSetTexture( action::SetTextureAction* data ) {
	texture::TextureAtlas textureAtlas( data->path_, data->, data->textureCount_ );

	pAssetManager_->getChunkMeshBuilder()->setTextureAtlas( pAssetManager_->getRenderer()->getTextureAtlas() );
}

void Engine::doSetShader( action::SetShaderAction* data ) {
	auto shader = std::unique_ptr<rendering::shader::IShader>( (rendering::shader::IShader*)new rendering::shader::ChunkShader() );
	shader->addShader( data->vertexShaderPath_, rendering::shader::ShaderType::Vertex );
	shader->addShader( data->fragmentShaderPath_, rendering::shader::ShaderType::Fragment );
	shader->compile();

	pRenderer_->setShader( std::move( shader ), rendering::ShaderType::Chunk );
}

void Engine::doCreateCamera( action::CreateCameraAction* data ) {
	pRenderer_->setCamera( std::make_unique<rendering::Camera>( data->x_, data->y_, data->z_, data->pitch_, data->yaw_, data->roll_ ) );
	data->returnCallback_( 1 );
}

void Engine::doMoveCamera( action::MoveCameraAction* data ) {
	pRenderer_->getCamera()->move( data->dx_, data->dy_, data->dz_ );
}

void Engine::doRotateCamera( action::RotateCameraAction* data ) {
	pRenderer_->getCamera()->rotate( data->pitch_, data->yaw_, data->roll_ );
}

void Engine::doDraw() {
	// Generate delta time
	//float currentFrame = glfwGetTime();
	//deltaTime_ = currentFrame - lastFrame_;
	//lastFrame_ = currentFrame;

	// Clear current frame
	glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	pWorld_->draw( *pRenderer_ );

	glfwSwapBuffers( pRenderer_->getWindow().get() );
	glfwPollEvents();
	eventing::KeyEventHandler::pollEvents();

	if( isRunning_ ) {
		workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::DrawAction() ) );
	}
	else {
		if( statusCallback_ ) {
			statusCallback_( { eventing::StatusEventType::Stopped } );
		}
	}
}

void Engine::doStop() {
	isRunning_ = false;
}
