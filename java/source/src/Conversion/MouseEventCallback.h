#pragma once

#include <Eventing/MouseEvent.h>
#include <jni.h>
#include <sstream>


namespace conversion {


class MouseEventCallback {
public:
	static void construct( JNIEnv* env ) {
		env->GetJavaVM(&jvm_);
		jClass_ = env->FindClass(  );
	}

	static void destruct( JNIEnv* env ) {
		if( jCallbackObject_ ) {
			env->DeleteGlobalRef( jCallbackObject_ );
			jCallbackObject_ = nullptr;
		}
	}

	static void registerCallback( JNIEnv* env, jobject jCallback ) {
		jCallbackObject_ = env->NewGlobalRef( jCallback );
		if( !jCallbackObject_ ) {
			std::cout << __FUNCTION__ << ": Could not get global ref to callback!" << std::endl;
		}

		jClass_ = env->FindClass( CLASS_NAME );

		jMethodID_ = env->GetMethodID( jClass_, INVOKE_METHOD, INVOKE_SIGNATURE );
		if( !jMethodID_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not find method '" << INVOKE_METHOD << INVOKE_SIGNATURE << "' for class '" << CLASS_WORLDCOORDINATES << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

private:
	MouseEventCallback() = default;
	~MouseEventCallback() = default;

	static JavaVM* jvm_;
	static jclass jClass_;
	static jobject jCallbackObject_;
	static jmethodID jMethodID_;

	static constexpr const char* CLASS_NAME =		"Eventing/IKeyEventCallback";
	static constexpr const char* INVOKE_METHOD =	"invoke";
	static constexpr const char* INVOKE_SIGNATURE =	"(LEventing/MouseEvent;)V";

	static void callback( const MouseEvent& event ) {
		JNIEnv* env;
		int envStat = jvm_->GetEnv( (void**)& env, JNI_VERSION_1_8 );
		if( envStat == JNI_EDETACHED ) {
			if( jvm->AttachCurrentThread( (void**)& env, NULL ) ) {
				std::cout << "Failed to attach jvm" << std::endl;
			}
		}
		else if( envStat == JNI_EVERSION ) {
			std::cout << "GetEnv: version not supported" << std::endl;
		}

		auto jMouseEvent = javaConverter.toMouseEvent( env, event );

		env->CallVoidMethod( jCallbackObject_,jMethodID_, jMouseEvent );

		jvm->DetachCurrentThread();
	}
};


}
