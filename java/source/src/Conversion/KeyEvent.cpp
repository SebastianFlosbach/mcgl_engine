#include "KeyEvent.h"

#include <sstream>

#include "JNIHelper.h"
#include "KeyEventType.h"


static constexpr const char* CLASS_NAME = "Eventing/KeyEvent";
static constexpr const char* CONSTRUCTOR_SIGNATURE = "(LEventing/EKeyEventType;ID)V";


namespace conversion {


void KeyEvent::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
	constructorID_ = JNIHelper::findConstructor( env, clazz_, CONSTRUCTOR_SIGNATURE );
}

void KeyEvent::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

jobject KeyEvent::j_KeyEvent( JNIEnv* env, const eventing::KeyEvent& event ) {
	return env->NewObject( clazz_, constructorID_, KeyEventType::j_KeyEventType( env, event.type_ ), event.key_, event.timePressed_ );
}


}
