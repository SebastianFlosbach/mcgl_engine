#include "MCGLEngine.h"

#include <mcgl-engine.h>
#include <iostream>
#include <Eventing/KeyEvent.h>

#include "Conversion/jni_conversion.h"
#include "Conversion/JNIHelper.h"


JNIEXPORT void JNICALL Java_MCGLEngine_CreateEngine( JNIEnv* env, jobject ) {
	conversion::construct( env );
	
	CreateEngine();
}

JNIEXPORT void JNICALL Java_MCGLEngine_DestroyEngine( JNIEnv* env, jobject ) {
	DestroyEngine();

	conversion::destruct( env );
}

JNIEXPORT void JNICALL Java_MCGLEngine_CreateWindow( JNIEnv* env, jobject, jint width, jint height, jstring title ) {
	const char* cTitle = conversion::JNIHelper::createString( env, title );
	CreateWindow( width, height, cTitle );
	conversion::JNIHelper::destroyString( env, title, cTitle );
}

JNIEXPORT void JNICALL Java_MCGLEngine_CloseWindow( JNIEnv*, jobject ) {
	CloseWindow();
}

JNIEXPORT void JNICALL Java_MCGLEngine_Run( JNIEnv*, jobject ) {
	Run();
}

JNIEXPORT void JNICALL Java_MCGLEngine_Stop( JNIEnv*, jobject ) {
	Stop();
}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterBlockType( JNIEnv* env, jobject obj, jobject jBlock ) {
	auto block = conversion::Block::cpp_Block( env, jBlock );
}

JNIEXPORT void JNICALL Java_MCGLEngine_SetTextures( JNIEnv* env, jobject, jstring path, jint textureSize, jint textureCount ) {
	auto cPath = conversion::JNIHelper::createString( env, path );
	SetTextures( cPath, textureSize, textureCount );
	conversion::JNIHelper::destroyString( env, path, cPath );
}

JNIEXPORT void JNICALL Java_MCGLEngine_SetShader( JNIEnv* env, jobject, jstring vertexShaderPath, jstring fragmentShaderPath ) {
	auto cVertexShaderPath = conversion::JNIHelper::createString( env, vertexShaderPath );
	auto cFragmentShaderPath = conversion::JNIHelper::createString( env, fragmentShaderPath );

	SetShader( cVertexShaderPath, cFragmentShaderPath );

	conversion::JNIHelper::destroyString( env, fragmentShaderPath, cFragmentShaderPath );
	conversion::JNIHelper::destroyString( env, vertexShaderPath, cVertexShaderPath );
}

JNIEXPORT void JNICALL Java_MCGLEngine_AddChunk( JNIEnv* env, jobject, jobject jChunk ) {

}

JNIEXPORT void JNICALL Java_MCGLEngine_RemoveChunk( JNIEnv* env, jobject, jobject coordinates ) {
	auto cppCoordinates = conversion::ChunkCoordinates::cpp_ChunkCoordinates( env, coordinates );
	RemoveChunk( cppCoordinates.x_, cppCoordinates.z_ );
}

JNIEXPORT void JNICALL Java_MCGLEngine_CreateCamera( JNIEnv*, jobject, jfloat x, jfloat y, jfloat z, jfloat pitch, jfloat yaw, jfloat roll ) {
	CreateCamera( x, y, z, pitch, yaw, roll );
}

JNIEXPORT void JNICALL Java_MCGLEngine_MoveCamera( JNIEnv*, jobject, jfloat dx, jfloat dy, jfloat dz ) {
	MoveCamera( dx, dy, dz );
}

JNIEXPORT void JNICALL Java_MCGLEngine_RotateCamera( JNIEnv*, jobject, jfloat pitch, jfloat yaw, jfloat roll ) {
	RotateCamera( pitch, yaw, roll );
}

JNIEXPORT jfloat JNICALL Java_MCGLEngine_GetDeltaTime( JNIEnv*, jobject ) {
	return GetDeltaTime();
}

JNIEXPORT jobject JNICALL Java_MCGLEngine_GetCameraPosition( JNIEnv* env, jobject caller ) {
	auto coordinates = GetCameraPosition();
	return conversion::WorldCoordinates::j_WorldCoordinates( env, coordinates );
}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterKeyEventCallback( JNIEnv* env, jobject caller, jobject callback ) {
	conversion::KeyEventCallback::registerCallback( env, callback );
}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterMouseEventCallback( JNIEnv* env, jobject caller, jobject callback ) {
	conversion::MouseEventCallback::registerCallback( env, callback );
}