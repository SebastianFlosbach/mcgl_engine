#include "MCGLEngine.h"

#include <mcgl-engine.h>
#include <iostream>
#include <Eventing/KeyEvent.h>

#include "Conversion/ClassDefinitions.h"
#include "Conversion/CppToJavaConverter.h"
#include "Conversion/FieldIDCache.h"
#include "Conversion/MethodIDCache.h"
#include "Conversion/JavaToCppConverter.h"


static conversion::FieldIDCache fieldIDCache;
static conversion::MethodIDCache methodIDCache;

static conversion::JavaToCppConverter cppConverter{ fieldIDCache };
static conversion::CppToJavaConverter javaConverter{ fieldIDCache, methodIDCache };


JNIEXPORT void JNICALL Java_MCGLEngine_CreateEngine( JNIEnv*, jobject ) {
	CreateEngine();
}

JNIEXPORT void JNICALL Java_MCGLEngine_DestroyEngine( JNIEnv*, jobject ) {
	DestroyEngine();
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
	std::cout << "RegisterBlockType" << std::endl;

	auto block = cppConverter.toBlock( env, jBlock );

	std::cout << "Id: " << block.id_ << std::endl;
	std::cout << "IsTransparent: " << std::boolalpha << block.isTransparent_ << std::endl;
	std::cout << "LeftTextureId: " << block.leftTextureId_ << std::endl;
	std::cout << "RightTextureId: " << block.rightTextureId_ << std::endl;
	std::cout << "FrontTextureId: " << block.frontTextureId_ << std::endl;
	std::cout << "BackTextureId: " << block.backTextureId_ << std::endl;
	std::cout << "TopTextureId: " << block.topTextureId_ << std::endl;
	std::cout << "BottomTextureId: " << block.bottomTextureId_ << std::endl;
}

JNIEXPORT void JNICALL Java_MCGLEngine_SetTextures( JNIEnv*, jobject, jstring, jint, jint );

JNIEXPORT void JNICALL Java_MCGLEngine_SetShader( JNIEnv*, jobject, jstring, jstring );

JNIEXPORT void JNICALL Java_MCGLEngine_AddChunk( JNIEnv*, jobject, jobject );

JNIEXPORT void JNICALL Java_MCGLEngine_RemoveChunk( JNIEnv*, jobject, jobject );

JNIEXPORT void JNICALL Java_MCGLEngine_CreateCamera( JNIEnv*, jobject, jfloat x, jfloat y, jfloat z, jfloat pitch, jfloat yaw, jfloat roll ) {
	CreateCamera( x, y, z, pitch, yaw, roll );
}

JNIEXPORT void JNICALL Java_MCGLEngine_MoveCamera( JNIEnv*, jobject, jint, jfloat, jfloat, jfloat );

JNIEXPORT void JNICALL Java_MCGLEngine_RotateCamera( JNIEnv*, jobject, jint, jfloat, jfloat, jfloat );/*

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterMouseEventCallback( JNIEnv*, jobject, jobject );

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterStatusEventCallback( JNIEnv*, jobject, jobject );*/

JNIEXPORT jfloat JNICALL Java_MCGLEngine_GetDeltaTime( JNIEnv*, jobject );

JNIEXPORT jobject JNICALL Java_MCGLEngine_GetCameraPosition( JNIEnv* env, jobject caller ) {
	std::cout << "GetCameraPosition" << std::endl;

	return javaConverter.toWorldCoordinates( env, GetCameraPosition() );
}



JavaVM* jvm;
jobject jKeyEventCallbackObject;
jmethodID jKeyEventCallbackMethod;

void keyEventCallback( const KeyEvent& event ) {
	JNIEnv* env;
	int envStat = jvm->GetEnv( (void**)&env, JNI_VERSION_1_8 );
	if ( envStat == JNI_EDETACHED ) {
		std::cout << "GetEnv: not attached" << std::endl;
		if ( jvm->AttachCurrentThread( (void**)&env, NULL ) ) {
			std::cout << "Failed to attach jvm" << std::endl;
		}
	} else if ( envStat == JNI_EVERSION ) {
		std::cout << "GetEnv: version not supported" << std::endl;
	}

	auto jKeyEvent = javaConverter.toKeyEvent( env, event );

	env->CallVoidMethod( jKeyEventCallbackObject, jKeyEventCallbackMethod, jKeyEvent );

	jvm->DetachCurrentThread();
}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterKeyEventCallback( JNIEnv* env, jobject caller, jobject callback ) {
	env->GetJavaVM(&jvm);
	jKeyEventCallbackObject = env->NewGlobalRef( callback );
	if( jKeyEventCallbackObject == NULL ) {
		std::cout << "__FUNCTION__" << ": Could not get global ref to callback!" << std::endl;
		return;
	}

	jKeyEventCallbackMethod = methodIDCache.GetKeyEventCallbackInvoke( env );

	RegisterKeyEventCallback( keyEventCallback );
}

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterMouseEventCallback( JNIEnv *, jobject, jstring ) {

}