#pragma once

#include <jni.h>
#include <Eventing/KeyEvent.h>


namespace conversion {


jobject keyEvent( JNIEnv* env, KeyEvent event ) {
	jclass clazz = env->FindClass( "KeyEvent" );
	auto constructor = env->GetMethodID( clazz, "<init>", "(LKeyEventType;ID)V" );
	jobject javaType = env->NewObject( clazz, constructor, keyEventType( env, event.type_ ), event.key_, event.timePressed_ );

	if( env->ExceptionCheck() ) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	return javaType;
}


}