#pragma once

#include <jni.h>
#include <Eventing/MouseEvent.h>


namespace conversion {


class MouseEventType {
public:
	MouseEventType() = delete;
	~MouseEventType() = default;

	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static jobject j_MouseEventType( JNIEnv* env, const eventing::MouseEventType& type );

private:
	static jclass clazz_;
	static jfieldID buttonPressID_;
	static jfieldID buttonReleaseID_;
	static jfieldID scrollID_;
	static jfieldID moveID_;

};


}
