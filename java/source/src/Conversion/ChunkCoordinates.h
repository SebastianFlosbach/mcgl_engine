#pragma once

#include <jni.h>
#include <Coordinates/ChunkCoordinates.h>


namespace conversion {


class ChunkCoordinates {
public:
	ChunkCoordinates() = delete;
	~ChunkCoordinates() = default;

	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static coordinates::ChunkCoordinates cpp_ChunkCoordinates( JNIEnv* env, jobject jCoordinates );

private:
	static jclass clazz_;
	static jfieldID xFieldId_;
	static jfieldID zFieldId_;

};


}
