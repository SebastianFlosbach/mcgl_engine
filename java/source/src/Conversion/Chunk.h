#pragma once

#include <Chunk/Chunk.h>
#include <jni.h>


namespace conversion {


class Chunk {
public:
	Chunk() = delete;
	~Chunk() = default;

	void construct( JNIEnv* env );
	void destruct( JNIEnv* env );

	chunk::Chunk_ptr cpp_Chunk( JNIEnv* env, jobject jChunk );

private:
	static jclass clazz_;
	static jfieldID blocksFieldId_;
	static jfieldID positionFieldId_;

};


}