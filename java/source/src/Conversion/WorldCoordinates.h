#pragma once

#include <jni.h>
#include <Coordinates/WorldCoordinates.h>


namespace conversion {


class WorldCoordinates {
public:
	WorldCoordinates() = delete;
	~WorldCoordinates() = default;

	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static jobject j_WorldCoordinates( JNIEnv* env, coordinates::WorldCoordinates& coordinates );

private:
	static jclass clazz_;
	static jmethodID constructor_;

};


}