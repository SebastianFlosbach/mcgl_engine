#include "JNIHelper.h"

#include <iostream>
#include <sstream>


static constexpr const char* CONSTRUCTOR_NAME = "<init>";


namespace conversion {


const char* JNIHelper::createString( JNIEnv* env, jstring string ) {
	return env->GetStringUTFChars( string, nullptr );
}

void JNIHelper::destroyString( JNIEnv* env, jstring jString, const char* string ) {
	env->ReleaseStringUTFChars( jString, string );
}

jclass JNIHelper::findClass( JNIEnv* env, const char* name ) {
	return env->FindClass( name );
}

jclass JNIHelper::createClass( JNIEnv* env, const char* name ) {
	auto localClazz = env->FindClass( name );
	if( !localClazz ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not find class '" << name << "'!";
		std::cout << errorMsg.str() << std::endl;
		throw std::runtime_error( errorMsg.str() );
	}

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
		std::cout << errorMsg.str() << std::endl;
		throw std::runtime_error( errorMsg.str() );
	}

	return constructorID;
}

jmethodID JNIHelper::findMethod( JNIEnv* env, jclass clazz, const char* name, const char* signature ) {
	auto methodID = env->GetMethodID( clazz, name, signature );
	if( !methodID ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not find method '" << name << signature;
		std::cout << errorMsg.str() << std::endl;
		throw std::runtime_error( errorMsg.str() );
	}

	return methodID;
}

jfieldID JNIHelper::findField( JNIEnv* env, jclass clazz, const char* name, const char* signature ) {
	auto fieldID = env->GetFieldID( clazz, name, signature );
	if( !fieldID ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not find field '" << name << "'!";
		std::cout << errorMsg.str() << std::endl;
		throw std::runtime_error( errorMsg.str() );
	}

	return fieldID;
}

jfieldID JNIHelper::findStaticField( JNIEnv* env, jclass clazz, const char* name, const char* signature ) {
	auto fieldID = env->GetStaticFieldID( clazz, name, signature );
	if( !fieldID ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not find static field '" << name << "'!";
		std::cout << errorMsg.str() << std::endl;
		throw std::runtime_error( errorMsg.str() );
	}

	return fieldID;
}

jobject JNIHelper::getStaticObjectField( JNIEnv* env, jclass clazz, jfieldID field ) {
	auto jObject = env->GetStaticObjectField( clazz, field );
	if( !jObject ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not get static object!";
		std::cout << errorMsg.str() << std::endl;
		throw std::runtime_error( errorMsg.str() );
	}

	return jObject;
}


}
