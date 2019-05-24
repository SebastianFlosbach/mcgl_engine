#include "MouseEvent.h"

#include "JNIHelper.h"
#include "MouseEventType.h"


static constexpr const char* CLASS_NAME = "Eventing/MouseEvent";
static constexpr const char* CONSTRUCTOR_POSITION_SIGNATURE = "(LEventing/EMouseEventType;DD)V";
static constexpr const char* CONSTRUCTOR_BUTTON_SIGNATURE = "(LEventing/EMouseEventType;ID)V"


namespace conversion {


MouseEvent::clazz_{ nullptr };


static void MouseEvent::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
	constructorPositionID_ = JNIHelper::findConstructor( env, clazz_, CONSTRUCTOR_POSITION_SIGNATURE );
	constructorButtonID_ = JNIHelper::findConstructor( env, clazz_, CONSTRUCTOR_BUTTON_SIGNATURE );
}

static void MouseEvent::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

static jobject MouseEvent::j_MouseEvent( JNIEnv* env, const eventing::MouseEvent& event ) {

	if( event.type_ == eventing::MouseEventType::ButtonPess || eventing.type_ == eventing::MouseEventType::ButtonRelease ) {
		return env->NewObject( clazz_, constructorButtonID_, MouseEventType::j_MouseEventType( event.type_ ), event.data_.button_.button_, event.data_.button_.timePressed_ );
	}


}


}
