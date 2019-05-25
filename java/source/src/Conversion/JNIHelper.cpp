#include "JNIHelper.h"

#include <sstream>


namespace conversion {


static constexpr const char* CONSTRUCTOR_NAME = "<init>";


jclass JNIHelper::findClass( JNIEnv* env, const char* name ) {
	return env->FindClass( name );
}

jclass JNIHelper::createClass( JNIEnv* env, const char* name ) {
	auto localClazz = env->FindClass( name );

	return static_cast<jclass>( env->NewGlobalRef( localClazz ) );
}

void JNIHelper::destroyClass( JNIEnv* env, jclass clazz ) {
	env->DeleteGlobalRef( clazz );
}

jmethodID JNIHelper::findConstructor( JNIEnv* env, jclass clazz, const char* signature ) {
	auto constructorID = env->GetMethodID( clazz, CONSTRUCTOR_NAME, signature );
	if( !constructorID ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not find constructor with signature '" << signature << "'!";
		throw std::runtime_error( errorMsg.str() );
	}

	return constructorID;
}

jmethodID JNIHelper::findMethod( JNIEnv* env, jclass clazz, const char* name, const char* signature ) {
	auto methodID = env->GetMethodID( clazz, name, signature );
	if( !methodID ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not find method '" << name << signature;
		throw std::runtime_error( errorMsg.str() );
	}

	return methodID;
}

jfieldID JNIHelper::findStaticField( JNIEnv* env, jclass clazz, const char* name, const char* signature ) {
	auto fieldID = env->GetStaticFieldID( clazz, name, signature );
	if( !fieldID ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not find static field '" << name << "'!";
		throw std::runtime_error( errorMsg.str() );
	}

	return fieldID;
}

jobject JNIHelper::getStaticObjectField( JNIEnv* env, jclass clazz, jfieldID field ) {
	auto jObject = env->GetStaticObjectField( clazz, field );
	if( !jObject ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not get static object!";
		throw std::runtime_error( errorMsg.str() );
	}

	return jObject;
}


}
