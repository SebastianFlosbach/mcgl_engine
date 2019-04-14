#include "Engine.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <future>

#include "Helper/OpenGLDebug.h"
#include "Eventing/KeyEventHandler.h"
#include "Eventing/MouseEventHandler.h"

Engine::Engine( const ILogger& logger ) : logger_( logger ) {
	if( isRunning_.exchange( true ) ) {
		return;
	}

	workerThread_ = std::thread( [this]() {
		while( isRunning_ ) {
			std::unique_lock<std::mutex> lock( mQueue_ );

			if( workerQueue_.empty() ) {
				cvQueue_.wait( lock, [this]() { return workerQueue_.empty(); } );
			}

			doAction( workerQueue_.dequeue() );
		}
	} );

	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::EngineInitAction() ) );
}

void Engine::doAction( action::Action_ptr& action ) {
	switch( action->type() ) {
	case action::ActionType::AddChunkAction:
		doAddChunk( static_cast<action::AddChunkAction*>( action.get() ) );
		break;
	case action::ActionType::CloseWindowAction:
		doCloseWindow();
		break;
	case action::ActionType::CreateCameraAction:
		doCreateCamera( static_cast<action::CreateCameraAction*>( action.get() ) );
		break;
	case action::ActionType::CreateWindowAction:
		doCreateWindow( static_cast<action::CreateWindowAction*>( action.get() ) );
		break;
	case action::ActionType::DrawAction:
		doDraw();
		break;
	case action::ActionType::EngineInitAction:
		doEngine();
		break;
	case action::ActionType::MoveCameraAction:
		doMoveCamera( static_cast<action::MoveCameraAction*>( action.get() ) );
		break;
	case action::ActionType::RegisterBlockTypeAction:
		doAddBlockType( static_cast<action::RegisterBlockTypeAction*>( action.get() ) );
		break;
	case action::ActionType::RegisterKeyEventCallbackAction:
		doRegisterKeyEventCallback( static_cast<action::RegisterKeyEventCallbackAction*>( action.get() ) );
		break;
	case action::ActionType::RegisterMouseEventCallbackAction:
		doRegisterMouseEventCallback( static_cast<action::RegisterMouseEventCallbackAction*>( action.get() ) );
		break;
	case action::ActionType::RegisterStatusEventCallbackAction:
		doRegisterStatusEventCallback( static_cast<action::RegisterStatusEventCallbackAction*>( action.get() ) );
		break;
	case action::ActionType::RemoveChunkAction:
		doRemoveChunk( static_cast<action::RemoveChunkAction*>( action.get() ) );
		break;
	case action::ActionType::RotateCameraAction:
		doRotateCamera( static_cast<action::RotateCameraAction*>( action.get() ) );
		break;
	case action::ActionType::RunAction:
		doRun();
		break;
	case action::ActionType::SetShaderAction:
		doSetShader( static_cast<action::SetShaderAction*>( action.get() ) );
		break;
	case action::ActionType::SetTexturesAction:
		doSetTextures( static_cast<action::SetTexturesAction*>( action.get() ) );
		break;
	case action::ActionType::StopAction:
		doStop();
		break;
	default:
		break;
	}
}

void Engine::createWindow( const UNUM32 width, const UNUM32 height, const std::string& title ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::CreateWindowAction( width, height, title ) ) );
}

void Engine::closeWindow() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::CloseWindowAction() ) );
}

void Engine::addBlockType( const world::block::Block& block, UNUM32 id ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RegisterBlockTypeAction( block, id ) ) );
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

void Engine::addChunk( const NUM32 x, const NUM32 z, const world::chunk::Chunk& chunk ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::AddChunkAction( x, z, chunk ) ) );
}

void Engine::removeChunk( const UNUM32 x, const UNUM32 z ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RemoveChunkAction( x, z ) ) );
}

void Engine::setTextures( texture::TextureAtlas&& textureAtlas ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::SetTexturesAction( std::move( textureAtlas ) ) ) );
}

void Engine::setShader( Shader&& shader ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::SetShaderAction( std::move( shader ) ) ) );
}

UNUM32 Engine::createCamera( const double x, const double y, const double z, const double pitch, const double yaw, const double roll = 0.0 ) {
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

void Engine::moveCamera( const UNUM32 cameraId, const double dx, const double dy, const double dz ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::MoveCameraAction( cameraId, dx, dy, dz ) ) );
}

void Engine::rotateCamera( const UNUM32 cameraId, const double pitch, const double yaw, const double roll = 0.0 ) {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RotateCameraAction( cameraId, pitch, yaw, roll ) ) );
}

void Engine::run() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::RunAction() ) );
}

void Engine::draw() {
	workerQueue_.enqueue( std::unique_ptr<action::Action>( new action::DrawAction() ) );
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

	renderer_ = std::make_unique<Renderer>();
}

void Engine::doCreateWindow( const action::CreateWindowAction* data ) {
	info( logger_, "createWindow()" );

	window_ = Window( data->width_, data->height_, data->title_ );

	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}

void Engine::doCloseWindow() {
	window_.close();
}

void Engine::doAddBlockType( const action::RegisterBlockTypeAction* data ) {
	info( logger_, "addBlockType()" );

	blockLibrary_.addBlock( data->block_, data->id_ );
}

void Engine::doRegisterKeyEventCallback( const action::RegisterKeyEventCallbackAction* data ) {
	info( logger_, "registerKeyEventCallback" );

	KeyEventHandler::registerCallback( window_.get(), data->callback_ );
}

void Engine::doRegisterMouseEventCallback( const action::RegisterMouseEventCallbackAction* data ) {
	info( logger_, "registerMouseEventCallback" );

	MouseEventHandler::registerCallback( window_.get(), data->callback_ );
}

void Engine::doRegisterStatusEventCallback( const action::RegisterStatusEventCallbackAction* data ) {
	info( logger_, "registerStatusEventCallback" );

	statusCallback_ = data->callback_;
}

void Engine::doAddChunk( const action::AddChunkAction* data ) {
	world_.addChunk( data->x_, data->z_, data->chunk_ );
}

void Engine::doRemoveChunk( const action::RemoveChunkAction* data ) {
	world_.removeChunk( data->x_, data->z_ );
}

void Engine::doSetTextures( action::SetTexturesAction* data ) {
	renderer_->setTextures( std::move( data->textureAtlas_ ) );
}

void Engine::doSetShader( action::SetShaderAction* data ) {
	renderer_->setShader( std::move( data->shader_ ) );
}

void Engine::doCreateCamera( const action::CreateCameraAction* data ) {
	camera_ = Camera( data->x_, data->y_, data->z_, data->pitch_, data->yaw_, data->roll_ );
	data->returnCallback_( 1 );
}

void Engine::doMoveCamera( const action::MoveCameraAction* data ) {
	camera_.move( data->dx_, data->dy_, data->dz_ );
}

void Engine::doRotateCamera( const action::RotateCameraAction* data ) {
	camera_.rotate( data->pitch_, data->yaw_, data->roll_ );
}

void Engine::doRun() {

}

void Engine::doDraw() {

}

void Engine::doStop() {
	isRunning_ = false;
}