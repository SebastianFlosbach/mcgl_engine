#pragma once

#include <jni.h>
#include <Chunk/Block/Block.h>

#include "FieldIDCache.h"



namespace conversion {


class JavaToCppConverter {
public:
	JavaToCppConverter( FieldIDCache& fieldIDCache ) : fieldIDCache_( fieldIDCache ) {}
	~JavaToCppConverter() = default;

	chunk::block::Block toBlock( JNIEnv* env, jobject jBlock ) {
		jfieldID idFieldId =				fieldIDCache_.GetBlockId( env );
		jfieldID isTransparentFieldId =		fieldIDCache_.GetIsTransparent( env );
		jfieldID leftTextureIdFieldId =		fieldIDCache_.GetRightTextureId( env );
		jfieldID rightTextureIdFieldId =	fieldIDCache_.GetLeftTextureId( env );
		jfieldID frontTextureIdFieldId =	fieldIDCache_.GetFrontTextureId( env );
		jfieldID backTextureIdFieldId =		fieldIDCache_.GetBackTextureId( env );
		jfieldID topTextureIdFieldId =		fieldIDCache_.GetTopTextureId( env );
		jfieldID bottomTextureIdFieldId =	fieldIDCache_.GetBottomTextureId( env );

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
	FieldIDCache& fieldIDCache_;

};


}
