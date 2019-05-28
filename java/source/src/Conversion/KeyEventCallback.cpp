#include "KeyEventCallback.h"

#include <iostream>

#include "JNIHelper.h"
#include "KeyEvent.h"


static constexpr const char* INVOKE_METHOD = "invoke";
static constexpr const char* INVOKE_SIGNATURE = "(LEventing/Key/KeyEvent;)V";


namespace conversion {


JavaVM* KeyEventCallback::jvm_{ nullptr };
jobject KeyEventCallback::jCallbackObject_{ nullptr };
jmethodID KeyEventCallback::jMethodID_{ nullptr };

void KeyEventCallback::construct( JNIEnv* env ) {
	env->GetJavaVM( &jvm_ );
}

void KeyEventCallback::destruct( JNIEnv* env ) {
	if( jCallbackObject_ ) {
		env->DeleteGlobalRef( jCallbackObject_ );
		jCallbackObject_ = nullptr;
	}
}

void KeyEventCallback::registerCallback( JNIEnv* env, jobject jCallback ) {
	jCallbackObject_ = env->NewGlobalRef( jCallback );
	if( !jCallbackObject_ ) {
		std::cout << __FUNCTION__ << ": Could not get global ref to callback!" << std::endl;
	}

	auto clazz = env->GetObjectClass( jCallback );
	jMethodID_ = JNIHelper::findMethod( env, clazz, INVOKE_METHOD, INVOKE_SIGNATURE );
}

void KeyEventCallback::callback( const eventing::KeyEvent& event ) {
	JNIEnv* env;
	int envStat = jvm_->GetEnv( (void**)& env, JNI_VERSION_1_8 );
	if( envStat == JNI_EDETACHED ) {
		if( jvm_->AttachCurrentThread( (void**)& env, NULL ) ) {
			std::cout << "Failed to attach jvm" << std::endl;
		}
	}
	else if( envStat == JNI_EVERSION ) {
		std::cout << "GetEnv: version not supported" << std::endl;
	}

	auto jKeyEvent = KeyEvent::j_KeyEvent( env, event );

	env->CallVoidMethod( jCallbackObject_, jMethodID_, jKeyEvent );

	jvm_->DetachCurrentThread();
}


}
