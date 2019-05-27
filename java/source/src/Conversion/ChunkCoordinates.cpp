#include "ChunkCoordinates.h"

#include "JNIHelper.h"


static constexpr const char* CLASS_NAME = "ChunkCoordinates";
static constexpr const char* X_FIELD = "x_";
static constexpr const char* X_SIGNATURE = "I";
static constexpr const char* Z_FIELD = "z_";
static constexpr const char* Z_SIGNATURE = "I";


namespace conversion {


jclass ChunkCoordinates::clazz_{ nullptr };
jfieldID ChunkCoordinates::xFieldId_{ nullptr };
jfieldID ChunkCoordinates::zFieldId_{ nullptr };

void ChunkCoordinates::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
	xFieldId_ = JNIHelper::findField( env, clazz_, X_FIELD, X_SIGNATURE );
	zFieldId_ = JNIHelper::findField( env, clazz_, Z_FIELD, Z_SIGNATURE );
}

void ChunkCoordinates::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

coordinates::ChunkCoordinates ChunkCoordinates::cpp_ChunkCoordinates( JNIEnv* env, jobject jCoordinates ) {
	auto x = env->GetIntField( jCoordinates, xFieldId_ );
	auto z = env->GetIntField( jCoordinates, zFieldId_ );

	return { x, z };
}


}
