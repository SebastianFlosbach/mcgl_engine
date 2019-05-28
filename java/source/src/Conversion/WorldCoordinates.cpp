#include "WorldCoordinates.h"

#include <iostream>
#include <sstream>

#include "JNIHelper.h"


static constexpr const char* CLASS_NAME = "WorldCoordinates";
static constexpr const char* CONSTRUCTOR_SIGNATURE = "(FFF)V";


namespace conversion {


jclass WorldCoordinates::clazz_{ nullptr };
jmethodID WorldCoordinates::constructor_{ nullptr };

void WorldCoordinates::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
	constructor_ = JNIHelper::findConstructor( env, clazz_, CONSTRUCTOR_SIGNATURE );
}

void WorldCoordinates::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

jobject WorldCoordinates::j_WorldCoordinates( JNIEnv* env, coordinates::WorldCoordinates& coordinates ) {
	jobject jcoordinates = env->NewObject( clazz_, constructor_, coordinates.x_, coordinates.y_, coordinates.z_ );
	if( !jcoordinates ) {
		std::stringstream errorMsg;
		errorMsg << __FUNCTION__ << ": Could not create new object!";
		std::cout << errorMsg.str() << std::endl;
		throw std::runtime_error( errorMsg.str() );
	}

	return jcoordinates;
}


}