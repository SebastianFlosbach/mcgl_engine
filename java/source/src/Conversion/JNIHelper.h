#pragma once

#include <jni.h>


namespace conversion {


class JNIHelper {
public:
	static jclass findClass( JNIEnv* env, const char* name );
	static jclass createClass( JNIEnv* env, const char* name );
	static void destroyClass( JNIEnv* env, jclass clazz );
	static jmethodID findConstructor( JNIEnv* env, jclass clazz, const char* signature );
	static jmethodID findMethod( JNIEnv* env, jclass clazz, const char* name, const char* signature );
	static jfieldID findStaticField( JNIEnv* env, jclass clazz, const char* name, const char* signature );

};


}
