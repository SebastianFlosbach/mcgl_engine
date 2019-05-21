#pragma once

#include <jni.h>
#include <Coordinates/WorldCoordinates.h>
#include <Eventing/KeyEvent.h>

#include "ClassDefinitions.h"
#include "FieldIDCache.h"
#include "MethodIDCache.h"


namespace conversion {


class CppToJavaConverter {
public:
	CppToJavaConverter( FieldIDCache fieldIDCache, MethodIDCache& methodIDCache ) : fieldIDCache_( fieldIDCache ), methodIDCache_( methodIDCache ) {}
	~CppToJavaConverter() = default;

	jobject toWorldCoordinates( JNIEnv* env, coordinates::WorldCoordinates coordinates ) {
		auto clazz = env->FindClass( CLASS_WORLDCOORDINATES );

		auto constructor = methodIDCache_.GetWorldCoordinatesConstructor( env );

		auto jWorldCoordinates = env->NewObject( clazz, constructor, coordinates.x_, coordinates.y_, coordinates.z_ );
		if( jWorldCoordinates == NULL ) {
			std::cout << __FUNCTION__ << ": Could not find construct java class 'WorldCoordinates'" << std::endl;
		}

		return jWorldCoordinates;
	}

	jobject toKeyEvent( JNIEnv* env, KeyEvent event ) {

		auto clazz = env->FindClass( CLASS_KEYEVENT );
		if( clazz == NULL ) {
			std::cout << __FUNCTION__ << ": Could not find java class 'KeyEvent'" << std::endl;
			return NULL;
		}

		auto constructor = methodIDCache_.GetKeyEventConstructor( env );

		auto jKeyEvent = env->NewObject( clazz, constructor, toKeyEventType( env, event.type_ ), event.key_, event.timePressed_ );
		if( jKeyEvent == NULL ) {
			std::cout << __FUNCTION__ << ": Could not find construct java class 'KeyEvent'" << std::endl;
			return NULL;
		}

		return jKeyEvent;
	}

	jobject toKeyEventType( JNIEnv* env, KeyEventType type ) {
		jclass clazz = env->FindClass( ENUM_KEYEVENTTYPE );
		if( clazz == NULL ) {
			std::cout << __FUNCTION__ << ": Could not find java class 'KeyEventType'" << std::endl;
			return NULL;
		}

		jfieldID fieldID = env->GetStaticFieldID( clazz, to_string( type ), KEYEVENTTYPE_SIGNATURE );
		if( fieldID == NULL ) {
			std::cout << __FUNCTION__ << ": Could not get static field id for KeyEventType!" << std::endl;
			return NULL;
		}

		jobject javaType = env->GetStaticObjectField( clazz, fieldID );
		if( javaType == NULL ) {
			std::cout << __FUNCTION__ << ": Could not get static object field for KeyEventType::" << to_string( type ) << "!" << std::endl;
			return NULL;
		}

		return javaType;
	}

private:
	FieldIDCache& fieldIDCache_;
	MethodIDCache& methodIDCache_;

};


}