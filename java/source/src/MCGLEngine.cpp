#include "MCGLEngineInterface.h"

#include <mcgl-engine.h>
#include <iostream>
#include <Eventing/KeyEvent.h>

#include "Conversion/KeyEvent.h"
#include "Conversion/KeyEventType.h"


JNIEXPORT void JNICALL Java_MCGLEngine_CreateEngine( JNIEnv*, jobject ) {
	CreateEngine();
}

JNIEXPORT void JNICALL Java_MCGLEngine_DestroyEngine( JNIEnv*, jobject ) {
	DestroyEngine();
}

JNIEXPORT void JNICALL Java_MCGLEngine_CreateWindow( JNIEnv*, jobject, jint, jint, jstring ) {
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

}

JNIEXPORT void JNICALL Java_MCGLEngine_SetTextures( JNIEnv*, jobject, jstring, jint, jint );

JNIEXPORT void JNICALL Java_MCGLEngine_SetShader( JNIEnv*, jobject, jstring, jstring );

JNIEXPORT void JNICALL Java_MCGLEngine_AddChunk( JNIEnv*, jobject, jobject );

JNIEXPORT void JNICALL Java_MCGLEngine_RemoveChunk( JNIEnv*, jobject, jobject );

JNIEXPORT jint JNICALL Java_MCGLEngine_CreateCamera( JNIEnv*, jobject, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble );

JNIEXPORT void JNICALL Java_MCGLEngine_MoveCamera( JNIEnv*, jobject, jint, jdouble, jdouble, jdouble );

JNIEXPORT void JNICALL Java_MCGLEngine_RotateCamera( JNIEnv*, jobject, jint, jdouble, jdouble, jdouble );

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterKeyEventCallback( JNIEnv*, jobject, jobject );

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterMouseEventCallback( JNIEnv*, jobject, jobject );

JNIEXPORT void JNICALL Java_MCGLEngine_RegisterStatusEventCallback( JNIEnv*, jobject, jobject );

JNIEXPORT jfloat JNICALL Java_MCGLEngine_GetDeltaTime( JNIEnv*, jobject );

JNIEXPORT jobject JNICALL Java_MCGLEngine_GetCameraPosition( JNIEnv*, jobject, jint );



JavaVM* jvm;
jobject jEventCallbackObject;
jmethodID jEventCallbackMethod;

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

	auto jKeyEvent = keyEvent( env, event );
	if ( jKeyEvent == nullptr ) {
		std::cout << "Java key event is nullptr" << std::endl;
		return;
	}

	env->CallVoidMethod( jEventCallbackObject, jEventCallbackMethod, jKeyEvent );

	if ( env->ExceptionCheck() ) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	jvm->DetachCurrentThread();
}

JNIEXPORT void JNICALL Java_MCGLEngineInterface_registerKeyEventCallback( JNIEnv* env, jobject obj, jstring callbackName ) {
	env->GetJavaVM(&jvm);
	jEventCallbackObject = env->NewGlobalRef( obj );

	jclass currentObjectClass = env->GetObjectClass( obj );
	if ( currentObjectClass == NULL ) {
		std::cout << "Failed to find class" << std::endl;
		return;
	}

	const char* cCallbackName = env->GetStringUTFChars( callbackName, NULL );
	jEventCallbackMethod = env->GetMethodID( currentObjectClass, cCallbackName, "(LKeyEvent;)V" );
	env->ReleaseStringUTFChars( callbackName, cCallbackName );

	if ( env->ExceptionCheck() ) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	if ( !jEventCallbackMethod ) {
		std::cout << "Could not find java callback method" << std::endl;
		return;
	}

	RegisterKeyEventCallback( keyEventCallback );
}

JNIEXPORT void JNICALL Java_MCGLEngineInterface_registerMouseEventCallback( JNIEnv *, jobject, jstring ) {

}