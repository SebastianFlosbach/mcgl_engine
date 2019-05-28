#include "MouseEvent.h"

#include <iostream>
#include <sstream>

#include "JNIHelper.h"
#include "MouseEventType.h"


static constexpr const char* CLASS_NAME = "Eventing/Mouse/MouseEvent";
static constexpr const char* CONSTRUCTOR_POSITION_SIGNATURE = "(LEventing/Mouse/EMouseEventType;DD)V";
static constexpr const char* CONSTRUCTOR_BUTTON_SIGNATURE = "(LEventing/Mouse/EMouseEventType;ID)V";


namespace conversion {


jclass MouseEvent::clazz_{ nullptr };
jmethodID MouseEvent::constructorPositionID_{ nullptr };
jmethodID MouseEvent::constructorButtonID_{ nullptr };

void MouseEvent::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
	constructorPositionID_ = JNIHelper::findConstructor( env, clazz_, CONSTRUCTOR_POSITION_SIGNATURE );
	constructorButtonID_ = JNIHelper::findConstructor( env, clazz_, CONSTRUCTOR_BUTTON_SIGNATURE );
}

void MouseEvent::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

jobject MouseEvent::j_MouseEvent( JNIEnv* env, const eventing::MouseEvent& event ) {

	if( event.type_ == eventing::MouseEventType::ButtonPess || event.type_ == eventing::MouseEventType::ButtonRelease ) {
		return env->NewObject( clazz_, constructorButtonID_, MouseEventType::j_MouseEventType( env, event.type_ ), event.data_.button_.button_, event.data_.button_.timePressed_ );
	}

	if( event.type_ == eventing::MouseEventType::Scroll ) {
		return env->NewObject( clazz_, constructorButtonID_, MouseEventType::j_MouseEventType( env, event.type_ ), event.data_.button_.button_, event.data_.button_.timePressed_ );
	}

	if( event.type_ == eventing::MouseEventType::Move ) {
		return env->NewObject( clazz_, constructorButtonID_, MouseEventType::j_MouseEventType( env, event.type_ ), event.data_.position_.x_, event.data_.position_.y_ );
	}

	std::stringstream errorMsg;
	errorMsg << __FUNCTION__ << ": Invalid MouseEventType 0x" << std::stringstream::hex << (int)event.type_ << "!";
	std::cout << errorMsg.str() << std::endl;
	throw std::runtime_error( errorMsg.str() );
}


}
