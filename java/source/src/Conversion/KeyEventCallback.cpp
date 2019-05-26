#include "KeyEventCallback.h"

#include "JNIHelper.h"
#include "KeyEvent.h"


static constexpr const char* INVOKE_METHOD = "invoke";
static constexpr const char* INVOKE_SIGNATURE = "(LEventing/KeyEvent;)V";


namespace conversion {


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

	jMethodID_ = JNIHelper::findMethod( env, (jclass)jCallbackObject_, INVOKE_METHOD, INVOKE_SIGNATURE );
}

void KeyEventCallback::callback( const eventing::KeyEvent& event ) {
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

	auto jKeyEvent = KeyEvent::j_KeyEvent( env, event );

	env->CallVoidMethod( jCallbackObject_, jMethodID_, jKeyEvent );

	jvm->DetachCurrentThread();
}


}
