#include "MouseEventType.h"

#include <jni.h>

#include "JNIHelper.h"


static constexpr const char* CLASS_NAME = "Eventing/Mouse/EMouseEventType";


namespace conversion {


static void MouseEventType::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
}

static void MouseEventType::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

static jobject MouseEventType::j_MouseEventType( JNIEnv* env, const eventing::MouseEventType& type ) {

}


}