#pragma once

#include <jni.h>
#include <Coordinates/WorldCoordinates.h>
#include <Eventing/KeyEvent.h>

#include "JavaDefinitions.h"


namespace conversion {

class CppToJavaConverter {
public:
	CppToJavaConverter() = default;
	~CppToJavaConverter() = default;

	jobject toWorldCoordinates( JNIEnv* env, coordinates::WorldCoordinates coordinates ) {
		auto clazz = env->FindClass( JAVA_CLASS_WORLD_COORDINATES );
		if( clazz == NULL ) {
			std::cout << "__FUNCTION__" << ": Could not find java class 'WorldCoordinates'" << std::endl;
		}

		auto constructor = env->GetMethodID( clazz, JAVA_METHOD_CONSTRUCTOR, JAVA_WORLD_COORDINATES_SIGNATURE_CONSTRUCTOR );
		if( constructor == NULL ) {
			std::cout << "__FUNCTION__" << ": Could not find constructor for java class 'WorldCoordinates'" << std::endl;
		}

		auto jWorldCoordinates = env->NewObject( clazz, constructor, coordinates.x_, coordinates.y_, coordinates.z_ );
		if( jWorldCoordinates == NULL ) {
			std::cout << "__FUNCTION__" << ": Could not find construct java class 'WorldCoordinates'" << std::endl;
		}

		return jWorldCoordinates;
	}

	jobject toKeyEvent( JNIEnv* env, KeyEvent event ) {

		auto clazz = env->FindClass( JAVA_CLASS_KEY_EVENT );
		if( clazz == NULL ) {
			std::cout << "__FUNCTION__" << ": Could not find java class 'KeyEvent'" << std::endl;
		}

		auto constructor = env->GetMethodID( clazz, "<init>", "(LKeyEventType;ID)V" );
		if( constructor == NULL ) {
			std::cout << "__FUNCTION__" << ": Could not find constructor for java class 'KeyEvent'" << std::endl;
		}

		auto jKeyEvent = env->NewObject( clazz, constructor, toKeyEventType( env, event.type_ ), event.key_, event.timePressed_ );
		if( jKeyEvent == NULL ) {
			std::cout << "__FUNCTION__" << ": Could not find construct java class 'KeyEvent'" << std::endl;
		}

		return jKeyEvent;
	}

	jobject toKeyEventType( JNIEnv* env, KeyEventType type ) {
		jclass clazz = env->FindClass( "KeyEventType" );
		jfieldID fieldId = env->GetStaticFieldID( clazz, to_string( type ), "LKeyEventType;" );
		jobject javaType = env->GetStaticObjectField( clazz, fieldId );

		return javaType;
	}

private:


};

}