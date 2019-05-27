#pragma once

#include <jni.h>


namespace conversion {


class JNIHelper {
public:
	static const char* createString( JNIEnv* env, jstring string );
	static void destroyString( JNIEnv* env, jstring jString, const char* string );
	static jclass findClass( JNIEnv* env, const char* name );
	static jclass createClass( JNIEnv* env, const char* name );
	static void destroyClass( JNIEnv* env, jclass clazz );
	static jmethodID findConstructor( JNIEnv* env, jclass clazz, const char* signature );
	static jmethodID findMethod( JNIEnv* env, jclass clazz, const char* name, const char* signature );
	static jfieldID findField( JNIEnv* env, jclass clazz, const char* name, const char* signature );
	static jfieldID findStaticField( JNIEnv* env, jclass clazz, const char* name, const char* signature );
	static jobject getStaticObjectField( JNIEnv* env, jclass clazz, jfieldID field );

};


}
