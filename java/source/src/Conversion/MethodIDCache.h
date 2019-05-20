#pragma once

#include <jni.h>


namespace conversion {


class MethodIDCache {
public:
	jmethodID GetKeyEventConstructor( JNIEnv* env );

	jmethodID GetKeyEventCallbackInvoke( JNIEnv* env );

	jmethodID GetWorldCoordinatesConstructor( JNIEnv* env );

private:
	jmethodID keyEventConstructor_;
	jmethodID keyEventCallbackInvoke_;
	jmethodID worldCoordinatesConstructor_;

private:
	static constexpr const char* METHOD_CONSTRUCTOR = "<init>";

	static constexpr const char* KEYEVENTCALLBACK_INVOKE_METHOD =		"invoke";
	static constexpr const char* KEYEVENTCALLBACK_INVOKE_SIGNATURE =	"(LEventing/KeyEvent;)V";

	static constexpr const char* KEYEVENT_CONSTRUCTOR_SIGNATURE = "(LEventing/EKeyEventType;IF)V";

	static constexpr const char* WORLDCOORDINATES_SIGNATURE_CONSTRUCTOR = "(FFF)V";

};


}
