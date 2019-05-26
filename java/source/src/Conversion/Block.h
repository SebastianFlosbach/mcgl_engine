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
	jfieldID idField_;
	jfieldID isTransparentField_;
	jfieldID leftTextureIdField_;
	jfieldID rightTextureIdField_;
	jfieldID frontTextureIdField_;
	jfieldID backTextureIdField_;
	jfieldID topTextureIdField_;
	jfieldID bottomTextureIdField_;

};


}