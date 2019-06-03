#include "MCGLEngine.h"

#include <mcgl-engine.h>
#include <iostream>
#include <Eventing/KeyEvent.h>

#include "Conversion/jni_conversion.h"
#include "Conversion/JNIHelper.h"


JNIEXPORT void JNICALL Java_MCGLEngine_CreateEngine( JNIEnv* env, jobject ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	conversion::construct( env );
	
	MCGLCreateEngine();
}

JNIEXPORT void JNICALL Java_MCGLEngine_DestroyEngine( JNIEnv* env, jobject ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	MCGLDestroyEngine();

	conversion::destruct( env );
}

JNIEXPORT void JNICALL Java_MCGLEngine_CreateWindow( JNIEnv* env, jobject, jint width, jint height, jstring title ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	const char* cTitle = conversion::JNIHelper::createString( env, title );
	MCGLCreateWindow( width, height, cTitle );
	conversion::JNIHelper::destroyString( env, title, cTitle );
}

JNIEXPORT void JNICALL Java_MCGLEngine_CloseWindow( JNIEnv*, jobject ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	MCGLCloseWindow();
}

JNIEXPORT void JNICALL Java_MCGLEngine_Run( JNIEnv*, jobject ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	MCGLRun();
}

JNIEXPORT void JNICALL Java_MCGLEngine_Stop( JNIEnv*, jobject ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	MCGLStop();
}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterBlockType( JNIEnv* env, jobject obj, jobject jBlock ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	auto block = conversion::Block::cpp_Block( env, jBlock );
	MCGLRegisterBlockType( block );
}

JNIEXPORT void JNICALL Java_MCGLEngine_SetTextures( JNIEnv* env, jobject, jstring path, jint textureSize, jint textureCount ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	auto cPath = conversion::JNIHelper::createString( env, path );
	MCGLSetTextures( cPath, textureSize, textureCount );
	conversion::JNIHelper::destroyString( env, path, cPath );
}

JNIEXPORT void JNICALL Java_MCGLEngine_SetShader( JNIEnv* env, jobject, jstring vertexShaderPath, jstring fragmentShaderPath ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	auto cVertexShaderPath = conversion::JNIHelper::createString( env, vertexShaderPath );
	auto cFragmentShaderPath = conversion::JNIHelper::createString( env, fragmentShaderPath );

	MCGLSetShader( cVertexShaderPath, cFragmentShaderPath );

	conversion::JNIHelper::destroyString( env, fragmentShaderPath, cFragmentShaderPath );
	conversion::JNIHelper::destroyString( env, vertexShaderPath, cVertexShaderPath );
}

JNIEXPORT void JNICALL Java_MCGLEngine_AddChunk( JNIEnv* env, jobject, jobject jChunk ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	auto chunk = conversion::Chunk::cpp_Chunk( env, jChunk );
	MCGLAddChunk( *chunk.get() );
}

JNIEXPORT void JNICALL Java_MCGLEngine_RemoveChunk( JNIEnv* env, jobject, jobject coordinates ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	auto cppCoordinates = conversion::ChunkCoordinates::cpp_ChunkCoordinates( env, coordinates );
	MCGLRemoveChunk( cppCoordinates.x_, cppCoordinates.z_ );
}

JNIEXPORT void JNICALL Java_MCGLEngine_CreateCamera( JNIEnv*, jobject, jfloat x, jfloat y, jfloat z, jfloat pitch, jfloat yaw, jfloat roll ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	MCGLCreateCamera( x, y, z, pitch, yaw, roll );
}

JNIEXPORT void JNICALL Java_MCGLEngine_MoveCamera( JNIEnv*, jobject, jfloat dx, jfloat dy, jfloat dz ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	MCGLMoveCamera( dx, dy, dz );
}

JNIEXPORT void JNICALL Java_MCGLEngine_RotateCamera( JNIEnv*, jobject, jfloat pitch, jfloat yaw, jfloat roll ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	MCGLRotateCamera( pitch, yaw, roll );
}

JNIEXPORT jobject JNICALL Java_MCGLEngine_GetCameraPosition( JNIEnv* env, jobject caller ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	auto coordinates = MCGLGetCameraPosition();
	return conversion::WorldCoordinates::j_WorldCoordinates( env, coordinates );
}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterKeyEventCallback( JNIEnv* env, jobject caller, jobject callback ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	conversion::KeyEventCallback::registerCallback( env, callback );
}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterMouseEventCallback( JNIEnv* env, jobject caller, jobject callback ) {
	std::cout << "[JNI] " << __FUNCTION__ << std::endl;

	conversion::MouseEventCallback::registerCallback( env, callback );
}