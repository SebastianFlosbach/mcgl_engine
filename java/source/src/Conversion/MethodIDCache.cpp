#include "MethodIDCache.h"

#include <exception>
#include <sstream>

#include "ClassDefinitions.h"


namespace conversion {


jmethodID MethodIDCache::GetKeyEventConstructor( JNIEnv* env ) {
	if( !keyEventConstructor_ ) {
		auto clazz = env->FindClass( CLASS_KEYEVENT );

		keyEventConstructor_ = env->GetMethodID( clazz, METHOD_CONSTRUCTOR, KEYEVENT_CONSTRUCTOR_SIGNATURE );
		if( !keyEventConstructor_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not find constructor '" << KEYEVENT_CONSTRUCTOR_SIGNATURE << "' for class '" << CLASS_KEYEVENT << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return keyEventConstructor_;
}
		  
jmethodID MethodIDCache::GetKeyEventCallbackInvoke( JNIEnv* env ) {
	if( !keyEventCallbackInvoke_ ) {
		auto clazz = env->FindClass( CLASS_KEYEVENTCALLBACK );

		keyEventCallbackInvoke_ = env->GetMethodID( clazz, KEYEVENTCALLBACK_INVOKE_METHOD, KEYEVENTCALLBACK_INVOKE_SIGNATURE );
		if( !keyEventCallbackInvoke_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not find method '" << KEYEVENTCALLBACK_INVOKE_METHOD << KEYEVENTCALLBACK_INVOKE_SIGNATURE << "' for class '" << CLASS_WORLDCOORDINATES << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return keyEventCallbackInvoke_;
}
		  
jmethodID MethodIDCache::GetWorldCoordinatesConstructor( JNIEnv* env ) {
	if( !worldCoordinatesConstructor_ ) {
		auto clazz = env->FindClass( CLASS_WORLDCOORDINATES );

		worldCoordinatesConstructor_ = env->GetMethodID( clazz, METHOD_CONSTRUCTOR, WORLDCOORDINATES_SIGNATURE_CONSTRUCTOR );
		if( !worldCoordinatesConstructor_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not find constructor '" << WORLDCOORDINATES_SIGNATURE_CONSTRUCTOR << "' for class '" << CLASS_WORLDCOORDINATES << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return worldCoordinatesConstructor_;
}


}
