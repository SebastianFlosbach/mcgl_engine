#include "mcgl-engine.h"

#include <Engine.h>
#include <Logging/SpdFileLogger.h>
#include <ActionHandling/ThreadedWorkerQueue.h>
#include <ActionHandling/actions.h>
#include <future>

#undef CreateWindow

const std::string loggerName { "mcgl_file_logger" };
const std::string loggerPath { "logs/mcgllog.log" };

std::unique_ptr<SpdFileLogger> logger;
std::unique_ptr<Engine> engine;


inline bool checkEngine() {
	if ( !engine ) {
		error( *logger, "Engine was not created!" );
		return false;
	}

	return true;
}

void CreateEngine() {
	logger = std::make_unique<SpdFileLogger>( loggerName, loggerPath );
	info( *logger, "[MCGL-ENGINE] CreateEngine" );

	engine = std::make_unique<Engine>( *logger );
}

void DestroyEngine() {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] DestroyEngine" );
	engine.reset();
}

void CreateWindow( const NUM32 width, const NUM32 height, const std::string& title ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] CreateWindow" );
	
	engineThread.enqueue( std::unique_ptr<action::Action>( new action::CreateWindowAction( width, height, title ) ) );
}

inline void doCreateWindow(const action::CreateWindowAction* data) {
	engine->createWindow(data->width_, data->height_, data->title_);
}

void CloseWindow() {
	if ( !checkEngine() ) return;

	info(*logger, "[MCGL-ENGINE] CloseWindow");
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::CloseWindowAction()));
}

inline void doCloseWindow() {
	engine->closeWindow();
}

void Run() {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] Run" );
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::RunAction() ) );
}

inline void doRun() {
	engine->run();
}

void Stop() {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] Stop" );
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::StopAction()));
}

inline void doStop() {
	engine->stop();
}

void RegisterBlockType( const world::block::Block& block, const NUM32 id ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RegisterBockType" );
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::RegisterBlockTypeAction(block, id)));
}

inline void doRegisterBlockType(const action::RegisterBlockTypeAction* data) {
	engine->addBlockType(data->block_, data->id_);
}

void SetTextures( const char* path, const UNUM32 textureSize, const UNUM32 textureCount ) {
	if ( !checkEngine() ) return;

	info(*logger, "[MCGL-ENGINE] SetTextures");
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::SetTexturesAction(path, textureSize, textureCount)));
}

inline void doSetTextures(const action::SetTexturesAction* data) {
	texture::TextureAtlas textureAtlas(data->path_, data->textureSize_, data->textureCount_);

	engine->setTextures(std::move(textureAtlas));
}

void SetShader( const char* vertexShaderPath, const char* fragmentShaderPath ) {
	if ( !checkEngine() ) return;

	info(*logger, "[MCGL-ENGINE] SetShader");
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::SetShaderAction(vertexShaderPath, fragmentShaderPath)));
}

inline void doSetShader(const action::SetShaderAction* data) {
	Shader shader = Shader();
	shader.addVertexShader(data->vertexPath_);
	shader.addFragmentShader(data->fragmentPath_);
	shader.compile();

	engine->setShader(std::move(shader));
}

void AddChunk( const NUM32 x, const NUM32 z, const world::chunk::Chunk& chunk ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] AddChunk" );
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::AddChunkAction(x, z, chunk)));
}

inline void doAddChunk(const action::AddChunkAction* data) {
	engine->addChunk(data->x_, data->z_, data->chunk_);
}

void RemoveChunk(const NUM32 x, const NUM32 z) {
	if (!checkEngine()) return;

	info(*logger, "[MCGL-ENGINE] RemoveChunk");
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::RemoveChunkAction(x, z)));
}

inline void doRemoveChunk(const action::RemoveChunkAction* data) {
	engine->removeChunk(data->x_, data->z_);
}

UNUM32 CreateCamera( const double x, const double y, const double z, const double pitch, const double yaw, const double roll ) {
	if ( !checkEngine() ) return 0;

	info( *logger, "[MCGL-ENGINE] CreateCamera" );
	
	unsigned int cameraId_ = 0;
	std::promise<void> promise = std::promise<void>();
	auto future = promise.get_future();

	engineThread.enqueue(std::unique_ptr<action::Action>(new action::CreateCameraAction(x, y, z, pitch, yaw, roll, [&cameraId_, &promise](unsigned int cameraId) {
		cameraId_ = cameraId;
		promise.set_value();
	})));

	future.wait();
	return cameraId_;
}

inline void doCreateCamera(const action::CreateCameraAction* data) {
	auto cameraId = engine->createCamera(data->x_, data->y_, data->z_, data->pitch_, data->yaw_, data->roll_);
	data->returnCallback_(cameraId);
}

void MoveCamera( const UNUM32 cameraId, const double dx, const double dy, const double dz ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] MoveCamera" );
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::MoveCameraAction(cameraId, dx, dy, dz)));
}

inline void doMoveCamera(const action::MoveCameraAction* data) {
	engine->moveCamera(data->cameraId_, data->dx_, data->dy_, data->dz_);
}

void RotateCamera( const UNUM32 cameraId, const double pitch, const double yaw, const double roll ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RotateCamera" );
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::RotateCameraAction(cameraId, pitch, yaw, roll)));
}

inline void doRotateCamera(const action::RotateCameraAction* data) {
	engine->rotateCamera(data->cameraId_, data->pitch_, data->yaw_, data->roll_);
}

void RegisterKeyEventCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RegisterKeyEventCallback" );
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::RegisterKeyEventCallbackAction(callback)));
}

inline void doRegisterKeyEventCallback(const action::RegisterKeyEventCallbackAction* data) {
	engine->registerKeyEventCallback(data->callback_);
}

void RegisterMouseEventCallback( MCGL_MOUSE_EVENT_CALLBACK callback ) {
	if ( !checkEngine() ) return;

	info( *logger, "[MCGL-ENGINE] RegisterMouseEventCallback" );
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::RegisterMouseEventCallbackAction(callback)));
}

inline void doRegisterMouseEventCallback(const action::RegisterMouseEventCallbackAction* data) {
	engine->registerMouseEventCallback(data->callback_);
}

void RegisterStatusEventCallback( MCGL_STATUS_EVENT_CALLBACK callback ) {
	engineThread.enqueue(std::unique_ptr<action::Action>(new action::RegisterStatusEventCallbackAction(callback)));
}

inline void doRegisterStatusEventCallback(const action::RegisterStatusEventCallbackAction* data) {
	engine->registerStatusEventCallback(data->callback_);
}

float GetDeltaTime() {
	if ( !checkEngine() ) return -1.0f;

	return engine->getDeltaTime();
}
