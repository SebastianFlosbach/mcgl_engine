#pragma once

#include <Eventing/MouseEvent.h>
#include <jni.h>
#include <sstream>


namespace conversion {


class MouseEventCallback {
public:
	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static void registerCallback( JNIEnv* env, jobject jCallback );

private:
	MouseEventCallback() = default;
	~MouseEventCallback() = default;

	static JavaVM* jvm_;
	static jobject jCallbackObject_;
	static jmethodID jMethodID_;

	static void callback( const eventing::MouseEvent& event );
};


}
