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


Engine::Engine( const logging::ILogger& logger ) :
	logger_( logger ),
	pWindow_( Window::create() ) {

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

void Engine::addMesh( const coordinates::WorldCoordinates& position, mesh::TexturedMesh* mesh ) {
	auto mesh_ptr = std::unique_ptr<mesh::TexturedMesh>( mesh );

	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::AddMeshAction( position, std::move( mesh_ptr ) ) ) );
}

void Engine::doAddMesh( action::AddMeshAction* data ) {
	pAssetManager_->getWorld()->addMesh( data->position_, std::move( data->pMesh_ ) );
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

void Engine::setSkyboxTexture(
	const std::string& right,
	const std::string& left,
	const std::string& top,
	const std::string& bottom,
	const std::string& front,
	const std::string& back
) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::SetSkyboxTextureAction( 
		right,
		left,
		top,
		bottom,
		front,
		back
	) ) );
}

void Engine::doSetSkyboxTexture( action::SetSkyboxTextureAction* data ) {
	pAssetManager_->getWorld()->setSkybox(
		data->right_,
		data->left_,
		data->top_,
		data->bottom_,
		data->front_,
		data->back_
	);
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

void Engine::moveCamera( double dx, double dy, double dz ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::MoveCameraAction( dx, dy, dz ) ) );
}

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

	pAssetManager_->setChunkMeshBuilder( new chunk::builder::ThreadedChunkMeshBuilder( logger_, 4 ) );

	if( isRunning_.exchange( true ) ) {
		return;
	}

	pAssetManager_->getChunkMeshBuilder()->setBlockLibrary( pAssetManager_->getBlockLibrary() );
	pAssetManager_->getChunkMeshBuilder()->registerCallback( chunk::builder::CHUNK_MESH_BUILDER_CALLBACK( [this]( const coordinates::ChunkCoordinates& position, mesh::TexturedMesh* mesh ) {
		addMesh( position.toWorldCoordinates(), mesh );
	} ) );

	pAssetManager_->getChunkCollection()->registerCollectionChangedCallback( chunk::CHUNK_COLLECTION_CHANGED_CALLBACK(
		[this]( const chunk::ChunkCollectionChangedEventType& type, const coordinates::ChunkCoordinates& position ) {
			switch( type ) {
			case chunk::ChunkCollectionChangedEventType::ChunkAdded:
				pAssetManager_->getChunkMeshBuilder()->build( position, *pAssetManager_->getChunkCollection() );
				break;
			case chunk::ChunkCollectionChangedEventType::ChunkRemoved:
				pAssetManager_->getWorld()->removeMesh( position.toWorldCoordinates() );
				break;
			default:
				break;
			}
		} )
	);
}

void Engine::doCreateWindow( action::CreateWindowAction* data ) {
	info( logger_, "createWindow()" );

	pWindow_->open( data->width_, data->height_, data->title_ );
	pWindow_->registerResizeCallback( MCGL_WINDOW_RESIZE_CALLBACK( [this]( NUM32 width, NUM32 height ) {
		pAssetManager_->getRenderer()->setProjectionMatrix( glm::perspective( glm::radians( 45.0f ), (float)width / (float)height, 0.1f, 500.0f ) );
	} ) );

	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glfwSetInputMode( pWindow_->get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	glEnable( GL_DEPTH_TEST );
}

void Engine::doCloseWindow() {
	pWindow_->close();
}

void Engine::doRegisterBlockType( action::RegisterBlockTypeAction* data ) {
	info( logger_, "addBlockType()" );

	pAssetManager_->getBlockLibrary()->registerBlock( data->block_ );
}

void Engine::doRegisterKeyEventCallback( action::RegisterKeyEventCallbackAction* data ) {
	info( logger_, "registerKeyEventCallback" );

	eventing::KeyEventHandler::registerCallback( pWindow_->get(), data->callback_ );
}

void Engine::doRegisterMouseEventCallback( action::RegisterMouseEventCallbackAction* data ) {
	info( logger_, "registerMouseEventCallback" );

	eventing::MouseEventHandler::registerCallback( pWindow_->get(), data->callback_ );
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

void Engine::doSetTextures( action::SetTexturesAction* data ) {
	texture::TextureAtlas textureAtlas( data->texturePath_, data->size_, data->textureCount_ );

	pAssetManager_->getRenderer()->setTextures( std::move( textureAtlas ) );
	pAssetManager_->getChunkMeshBuilder()->setTextureAtlas( pAssetManager_->getRenderer()->getTextureAtlas() );
}

void Engine::doSetShader( action::SetShaderAction* data ) {
	Shader shader = Shader();
	shader.addVertexShader( data->vertexShaderPath_ );
	shader.addFragmentShader( data->fragmentShaderPath_ );
	shader.compile();

	pAssetManager_->getRenderer()->setShader( std::move( shader ), ShaderType::Chunk );
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


	pAssetManager_->getRenderer()->setViewMatrix( camera_.getView() );

	pAssetManager_->getWorld()->draw( *pAssetManager_->getRenderer() );

	glfwSwapBuffers( pWindow_->get() );
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
