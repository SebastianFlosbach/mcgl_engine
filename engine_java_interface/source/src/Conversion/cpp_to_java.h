#pragma once

#include <jni.h>
#include <Eventing/keyevent.h>
#include <iostream>

jobject keyEvent( JNIEnv* env, KeyEvent event );
jobject keyEventType( JNIEnv* env, KeyEventType type );


jobject keyEvent( JNIEnv* env, KeyEvent event ) {
	std::cout << "Converting keyEvent to java" << std::endl;
	jclass clazz = env->FindClass( "KeyEvent" );
	auto constructor = env->GetMethodID( clazz, "<init>", "(LKeyEventType;ID)V" );
	jobject javaType = env->NewObject( clazz, constructor, keyEventType( env, event.type_ ), event.key_, event.timePressed_ );

	if ( env->ExceptionCheck() ) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	return javaType;
}

jobject keyEventType( JNIEnv* env, KeyEventType type ) {
	std::cout << "Converting keyEventType to java" << std::endl;
	jclass clazz = env->FindClass( "KeyEventType" );
	jfieldID fieldId = env->GetStaticFieldID( clazz, to_string( type ), "LKeyEventType;" );
	jobject javaType = env->GetStaticObjectField( clazz, fieldId );

	if ( env->ExceptionCheck() ) {
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	return javaType;
}