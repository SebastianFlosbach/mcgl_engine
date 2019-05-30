#pragma once

#include <Chunk/Chunk.h>
#include <jni.h>


namespace conversion {


class Chunk {
public:
	Chunk() = delete;
	~Chunk() = default;

	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static chunk::Chunk_ptr cpp_Chunk( JNIEnv* env, jobject jChunk );

private:
	static jclass clazz_;
	static jfieldID blocksFieldId_;
	static jfieldID positionFieldId_;

};


}
