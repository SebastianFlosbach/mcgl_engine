#pragma once

#include <jni.h>
#include <Eventing/KeyEvent.h>


namespace conversion {


jobject keyEventType( JNIEnv* env, KeyEventType type ) {
	jclass clazz = env->FindClass( "KeyEventType" );
	jfieldID fieldId = env->GetStaticFieldID( clazz, to_string( type ), "LKeyEventType;" );
	jobject javaType = env->GetStaticObjectField( clazz, fieldId );

	if( env->ExceptionCheck() ) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	return javaType;
}


}