#include "MouseEventType.h"

#include <jni.h>
#include <sstream>

#include "JNIHelper.h"


static constexpr const char* CLASS_NAME = "Eventing/Mouse/EMouseEventType";
static constexpr const char* CLASS_SIGNATURE = "LEventing/Mouse/EMouseEventType;";
static constexpr const char* BUTTONPRESS_FIELD = "ButtonPress";
static constexpr const char* BUTTONRELEASE_FIELD = "ButtonRelease";
static constexpr const char* SCROLL_FIELD = "Scroll";
static constexpr const char* MOVE_FIELD = "Move";


namespace conversion {


void MouseEventType::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
	buttonPressID_ = JNIHelper::findStaticField( env, clazz_, BUTTONPRESS_FIELD, CLASS_SIGNATURE );
	buttonReleaseID_ = JNIHelper::findStaticField( env, clazz_, BUTTONRELEASE_FIELD, CLASS_SIGNATURE );
	buttonPressID_ = JNIHelper::findStaticField( env, clazz_, SCROLL_FIELD, CLASS_SIGNATURE );
	buttonPressID_ = JNIHelper::findStaticField( env, clazz_, MOVE_FIELD, CLASS_SIGNATURE );
}

void MouseEventType::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

jobject MouseEventType::j_MouseEventType( JNIEnv* env, const eventing::MouseEventType& type ) {
	switch( type )
	{
	case eventing::MouseEventType::ButtonPess:
		return env->GetStaticObjectField( clazz_, buttonPressID_ );
	case eventing::MouseEventType::ButtonRelease:
		return env->GetStaticObjectField( clazz_, buttonReleaseID_ );		
	case eventing::MouseEventType::Scroll:
		return env->GetStaticObjectField( clazz_, scrollID_ );
	case eventing::MouseEventType::Move:
		return env->GetStaticObjectField( clazz_, moveID_ );
		break;
	default: {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Invalid MouseEventType 0x" << std::stringstream::hex << type << "!";
		throw std::runtime_error( errorMsg.str() );
	}
		break;
	}
}


}