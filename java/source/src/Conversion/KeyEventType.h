#pragma once

#include <jni.h>
#include <Eventing/KeyEvent.h>


namespace conversion {


class KeyEventType {
public:
	KeyEventType() = delete;
	~KeyEventType() = default;

	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static jobject j_KeyEventType( JNIEnv* env, const eventing::KeyEventType& type );

private:
	static jclass clazz_;
	static jfieldID pressedID_;
	static jfieldID downID_;
	static jfieldID releasedID_;

};


}
