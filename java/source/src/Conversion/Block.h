#pragma once

#include <Chunk/Block/Block.h>
#include <jni.h>


namespace conversion {


class Block {
public:
	Block() = delete;
	~Block() = default;

	static void construct( JNIEnv* env );
	static void destruct( JNIEnv* env );

	static chunk::block::Block cpp_Block( JNIEnv* env, jobject block );

private:
	static jclass clazz_;

	static jfieldID idField_;
	static jfieldID isTransparentField_;
	static jfieldID leftTextureIdField_;
	static jfieldID rightTextureIdField_;
	static jfieldID frontTextureIdField_;
	static jfieldID backTextureIdField_;
	static jfieldID topTextureIdField_;
	static jfieldID bottomTextureIdField_;

};


}