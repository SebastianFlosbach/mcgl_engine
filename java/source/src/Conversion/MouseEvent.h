#pragma once

#include <jni.h>
#include <Eventing/MouseEvent.h>


namespace conversion {


class MouseEvent {
public:
	MouseEvent() = delete;
	~MouseEvent() = default;

	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static jobject j_MouseEvent( JNIEnv* env, const eventing::MouseEvent& event );

private:
	static jclass clazz_;
	static jmethodID constructorPositionID_;
	static jmethodID constructorButtonID_;

};


}