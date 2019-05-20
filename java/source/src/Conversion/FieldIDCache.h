#pragma once

#include <jni.h>


namespace conversion {

class FieldIDCache {
public:
	FieldIDCache() = default;

	jfieldID GetBlockId( JNIEnv* env );
	jfieldID GetIsTransparent( JNIEnv* env );
	jfieldID GetLeftTextureId( JNIEnv* env );
	jfieldID GetRightTextureId( JNIEnv* env );
	jfieldID GetTopTextureId( JNIEnv* env );
	jfieldID GetBottomTextureId( JNIEnv* env );
	jfieldID GetFrontTextureId( JNIEnv* env );
	jfieldID GetBackTextureId( JNIEnv* env );

	jfieldID GetKeyEventType( JNIEnv* env, const char* name );

private:
	jfieldID blockId_;
	jfieldID blockIsTransparent_;
	jfieldID blockLeftTextureId_;
	jfieldID blockRightTextureId_;
	jfieldID blockTopTextureId_; 
	jfieldID blockBottomTextureId_;
	jfieldID blockFrontTextureId_;
	jfieldID blockBackTextureId_;

private:
	static constexpr const char* BLOCK_ID_FIELD = "id_";
	static constexpr const char* BLOCK_ID_SIGNATURE = "I";
	static constexpr const char* BLOCK_ISTRANSPARENT_FIELD = "isTransparent_";
	static constexpr const char* BLOCK_ISTRANSPARENT_SIGNATURE = "Z";
	static constexpr const char* BLOCK_LEFTTEXTUREID_FIELD = "leftTextureId_";
	static constexpr const char* BLOCK_LEFTTEXTUREID_SIGNATURE = "I";
	static constexpr const char* BLOCK_RIGHTTEXTUREID_FIELD = "rightTextureId_";
	static constexpr const char* BLOCK_RIGHTTEXTUREID_SIGNATURE = "I";
	static constexpr const char* BLOCK_TOPTEXTUREID_FIELD = "topTextureId_";
	static constexpr const char* BLOCK_TOPTEXTUREID_SIGNATURE = "I";
	static constexpr const char* BLOCK_BOTTOMTEXTUREID_FIELD = "bottomTextureId_";
	static constexpr const char* BLOCK_BOTTOMTEXTUREID_SIGNATURE = "I";
	static constexpr const char* BLOCK_FRONTTEXTUREID_FIELD = "frontTextureId_";
	static constexpr const char* BLOCK_FRONTTEXTUREID_SIGNATURE = "I";
	static constexpr const char* BLOCK_BACKTEXTUREID_FIELD = "backTextureId_";
	static constexpr const char* BLOCK_BACKTEXTUREID_SIGNATURE = "I";


};


}
