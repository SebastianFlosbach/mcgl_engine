#pragma once

#include <Eventing/KeyEvent.h>
#include <jni.h>


namespace conversion {


class KeyEventCallback {
public:
	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static void registerCallback( JNIEnv* env, jobject jCallback );

private:
	KeyEventCallback() = default;
	~KeyEventCallback() = default;

	static JavaVM* jvm_;
	static jobject jCallbackObject_;
	static jmethodID jMethodID_;

	static void callback( const eventing::KeyEvent& event );
};


}
