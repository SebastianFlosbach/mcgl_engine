#include "KeyEventType.h"

#include <jni.h>
#include <sstream>

#include "JNIHelper.h"


static constexpr const char* CLASS_NAME = "Eventing/Key/EKeyEventType";
static constexpr const char* CLASS_SIGNATURE = "LEventing/Key/EKeyEventType;";
static constexpr const char* PRESSED_FIELD = "Pressed";
static constexpr const char* DOWN_FIELD = "Down";
static constexpr const char* RELEASED_FIELD = "Released";


namespace conversion {


jclass KeyEventType::clazz_{ nullptr };
jfieldID KeyEventType::pressedID_{ nullptr };
jfieldID KeyEventType::downID_{ nullptr };
jfieldID KeyEventType::releasedID_{ nullptr };

void KeyEventType::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
	pressedID_ = JNIHelper::findStaticField( env, clazz_, PRESSED_FIELD, CLASS_SIGNATURE );
	downID_ = JNIHelper::findStaticField( env, clazz_, DOWN_FIELD, CLASS_SIGNATURE );
	releasedID_ = JNIHelper::findStaticField( env, clazz_, RELEASED_FIELD, CLASS_SIGNATURE );
}

void KeyEventType::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

jobject KeyEventType::j_KeyEventType( JNIEnv* env, const eventing::KeyEventType& type ) {
	switch( type )
	{
	case eventing::KeyEventType::Pressed:
		return env->GetStaticObjectField( clazz_, pressedID_ );
	case eventing::KeyEventType::Down:
		return env->GetStaticObjectField( clazz_, downID_ );
	case eventing::KeyEventType::Released:
		return env->GetStaticObjectField( clazz_, releasedID_ );
	default: {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Invalid KeyEventType 0x" << std::stringstream::hex << (int)type << "!";
		throw std::runtime_error( errorMsg.str() );
	}
		break;
	}
}


}