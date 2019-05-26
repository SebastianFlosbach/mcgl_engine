#include "MCGLEngine.h"

#include <mcgl-engine.h>
#include <iostream>
#include <Eventing/KeyEvent.h>

#include "Conversion/jni_conversion.h"


JNIEXPORT void JNICALL Java_MCGLEngine_CreateEngine( JNIEnv* env, jobject ) {
	conversion::construct( env );
	
	CreateEngine();
}

JNIEXPORT void JNICALL Java_MCGLEngine_DestroyEngine( JNIEnv* env, jobject ) {
	DestroyEngine();

	conversion::destruct( env );
}

JNIEXPORT void JNICALL Java_MCGLEngine_CreateWindow( JNIEnv* env, jobject, jint width, jint height, jstring title ) {
	const char* cTitle = env->GetStringUTFChars( title, false );
	CreateWindow( width, height, cTitle );
	env->ReleaseStringUTFChars( title, cTitle );
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

JNIEXPORT void JNICALL Java_MCGLEngine_SetTextures( JNIEnv*, jobject, jstring, jint, jint );

JNIEXPORT void JNICALL Java_MCGLEngine_SetShader( JNIEnv*, jobject, jstring, jstring );

JNIEXPORT void JNICALL Java_MCGLEngine_AddChunk( JNIEnv*, jobject, jobject );

JNIEXPORT void JNICALL Java_MCGLEngine_RemoveChunk( JNIEnv*, jobject, jobject );

JNIEXPORT void JNICALL Java_MCGLEngine_CreateCamera( JNIEnv*, jobject, jfloat x, jfloat y, jfloat z, jfloat pitch, jfloat yaw, jfloat roll ) {
	CreateCamera( x, y, z, pitch, yaw, roll );
}

JNIEXPORT void JNICALL Java_MCGLEngine_MoveCamera( JNIEnv*, jobject, jint, jfloat, jfloat, jfloat );

JNIEXPORT void JNICALL Java_MCGLEngine_RotateCamera( JNIEnv*, jobject, jint, jfloat, jfloat, jfloat );

JNIEXPORT jfloat JNICALL Java_MCGLEngine_GetDeltaTime( JNIEnv*, jobject );

JNIEXPORT jobject JNICALL Java_MCGLEngine_GetCameraPosition( JNIEnv* env, jobject caller ) {

}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterKeyEventCallback( JNIEnv* env, jobject caller, jobject callback ) {
	conversion::KeyEventCallback::registerCallback( env, callback );
}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterMouseEventCallback( JNIEnv* env, jobject caller, jobject callback ) {
	conversion::MouseEventCallback::registerCallback( env, callback );
}