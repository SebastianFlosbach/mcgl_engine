#include "MCGLEngineInterface.h"

#include <mcgl-engine.h>
#include <iostream>
#include <Eventing/KeyEvent.h>

#include "Conversion/cpp_to_java.h"

JNIEXPORT void JNICALL Java_MCGLEngineInterface_createEngine( JNIEnv *, jobject ) {
	std::cout << "createEngine()" << std::endl;
	CreateEngine();
}

JNIEXPORT void JNICALL Java_MCGLEngineInterface_createWindow( JNIEnv* env, jobject, jint width, jint height, jstring title ) {
	std::cout << "createWindow()" << std::endl;

	const char* cTitle = env->GetStringUTFChars( title, false );
	CreateWindow( width, height, cTitle );
	env->ReleaseStringUTFChars( title, cTitle );
}

JNIEXPORT void JNICALL Java_MCGLEngineInterface_run( JNIEnv* , jobject ) {
	Run();
}

JNIEXPORT void JNICALL Java_MCGLEngineInterface_stop( JNIEnv* , jobject ) {

}

JNIEXPORT void JNICALL Java_MCGLEngineInterface_destroyEngine( JNIEnv *, jobject ) {
	DestroyEngine();
}



JavaVM* jvm;
jobject jEventCallbackObject;
jmethodID jEventCallbackMethod;

void keyEventCallback( KeyEvent event ) {
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