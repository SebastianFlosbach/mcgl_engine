#pragma once

#include <jni.h>
#include <Chunk/Block/Block.h>

#include "JavaDefinitions.h"



namespace conversion {


class JavaToCppConverter {
public:
	JavaToCppConverter() = default;
	~JavaToCppConverter() = default;

	chunk::block::Block toBlock( JNIEnv* env, jobject jBlock ) {
		jclass clazz = env->FindClass( JAVA_CLASS_BLOCK );

		jfieldID idFieldId =				env->GetFieldID( clazz, JAVA_BLOCK_FIELD_ID,				JAVA_BLOCK_SIGNATURE_ID );
		jfieldID isTransparentFieldId =		env->GetFieldID( clazz, JAVA_BLOCK_FIELD_IS_TRANSPARENT,	JAVA_BLOCK_SIGNATURE_IS_TRANSPARENT );
		jfieldID leftTextureIdFieldId =		env->GetFieldID( clazz, JAVA_BLOCK_FIELD_LEFT_TEXTURE_ID,	JAVA_BLOCK_SIGNATURE_LEFT_TEXTURE_ID );
		jfieldID rightTextureIdFieldId =	env->GetFieldID( clazz, JAVA_BLOCK_FIELD_RIGHT_TEXTURE_ID,	JAVA_BLOCK_SIGNATURE_RIGHT_TEXTURE_ID );
		jfieldID frontTextureIdFieldId =	env->GetFieldID( clazz, JAVA_BLOCK_FIELD_FRONT_TEXTURE_ID,	JAVA_BLOCK_SIGNATURE_FRONT_TEXTURE_ID );
		jfieldID backTextureIdFieldId =		env->GetFieldID( clazz, JAVA_BLOCK_FIELD_BACK_TEXTURE_ID,	JAVA_BLOCK_SIGNATURE_BACK_TEXTURE_ID );
		jfieldID topTextureIdFieldId =		env->GetFieldID( clazz, JAVA_BLOCK_FIELD_TOP_TEXTURE_ID,	JAVA_BLOCK_SIGNATURE_TOP_TEXTURE_ID );
		jfieldID bottomTextureIdFieldId =	env->GetFieldID( clazz, JAVA_BLOCK_FIELD_BOTTOM_TEXTURE_ID, JAVA_BLOCK_SIGNATURE_BOTTOM_TEXTURE_ID );

		jint jId =					env->GetIntField(		jBlock, idFieldId );
		jboolean jIsTransparent =	env->GetBooleanField(	jBlock, isTransparentFieldId );
		jint jLeftTextureId =		env->GetIntField(		jBlock, leftTextureIdFieldId );
		jint jRightTextureId =		env->GetIntField(		jBlock, rightTextureIdFieldId );
		jint jFrontTextureId =		env->GetIntField(		jBlock, frontTextureIdFieldId );
		jint jBackTextureId =		env->GetIntField(		jBlock, backTextureIdFieldId );
		jint jTopTextureId =		env->GetIntField(		jBlock, topTextureIdFieldId );
		jint jBottomTextureId =		env->GetIntField(		jBlock, bottomTextureIdFieldId );

		UNUM32 id =					static_cast<UNUM32>(jId);
		bool isTransparent =		static_cast<bool>(jIsTransparent);
		UNUM32 leftTextureId =		static_cast<UNUM32>(jLeftTextureId);
		UNUM32 rightTextureId =		static_cast<UNUM32>(jRightTextureId);
		UNUM32 frontTextureId =		static_cast<UNUM32>(jFrontTextureId);
		UNUM32 backTextureId =		static_cast<UNUM32>(jBackTextureId);
		UNUM32 topTextureId =		static_cast<UNUM32>(jTopTextureId);
		UNUM32 bottomTextureId =	static_cast<UNUM32>(jBottomTextureId);

		return { id, isTransparent, leftTextureId, rightTextureId, frontTextureId, backTextureId, topTextureId, bottomTextureId };
	}

private:


};


}
