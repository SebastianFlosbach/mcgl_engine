#pragma once

#include <jni.h>
#include <Eventing/KeyEvent.h>


namespace conversion {


class KeyEvent {
public:
	KeyEvent() = delete;
	~KeyEvent() = default;

	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static jobject j_KeyEvent( JNIEnv* env, const eventing::KeyEvent& event );

private:
	static jclass clazz_;
	static jmethodID constructorID_;

};


}