#include "MCGLEngineInterface.h"

#include <mcgl-engine.h>

JNIEXPORT void JNICALL Java_MCGLEngineInterface_CreateEngine( JNIEnv *, jobject ) {
	CreateEngine();
}

JNIEXPORT void JNICALL Java_MCGLEngineInterface_CreateWindow( JNIEnv* env, jobject, jint width, jint height, jstring title ) {
	const char* cTitle = env->GetStringUTFChars( title, false );
	CreateWindow( width, height, cTitle );
	env->ReleaseStringUTFChars( title, cTitle );
}

JNIEXPORT void JNICALL Java_MCGLEngineInterface_Run( JNIEnv *, jobject ) {
	Run();
}

JNIEXPORT void JNICALL Java_MCGLEngineInterface_DestroyEngine( JNIEnv *, jobject ) {
	DestroyEngine();
}