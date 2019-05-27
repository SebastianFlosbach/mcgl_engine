#include "MouseEventCallback.h"

#include <iostream>

#include "JNIHelper.h"
#include "MouseEvent.h"


static constexpr const char* INVOKE_METHOD = "invoke";
static constexpr const char* INVOKE_SIGNATURE = "(LEventing/MouseEvent;)V";


namespace conversion {


JavaVM* MouseEventCallback::jvm_{ nullptr };
jobject MouseEventCallback::jCallbackObject_{ nullptr };
jmethodID MouseEventCallback::jMethodID_{ nullptr };

void MouseEventCallback::construct( JNIEnv* env ) {
	env->GetJavaVM( &jvm_ );
}

void MouseEventCallback::destruct( JNIEnv* env ) {
	if( jCallbackObject_ ) {
		env->DeleteGlobalRef( jCallbackObject_ );
		jCallbackObject_ = nullptr;
	}
}

void MouseEventCallback::registerCallback( JNIEnv* env, jobject jCallback ) {
	jCallbackObject_ = env->NewGlobalRef( jCallback );
	if( !jCallbackObject_ ) {
		std::cout << __FUNCTION__ << ": Could not get global ref to callback!" << std::endl;
	}

	jMethodID_ = JNIHelper::findMethod( env, (jclass)jCallbackObject_, INVOKE_METHOD, INVOKE_SIGNATURE );
}

void MouseEventCallback::callback( const eventing::MouseEvent& event ) {
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

	auto jMouseEvent = MouseEvent::j_MouseEvent( env, event );

	env->CallVoidMethod( jCallbackObject_, jMethodID_, jMouseEvent );

	jvm_->DetachCurrentThread();
}


}
