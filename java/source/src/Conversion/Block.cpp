#include "Block.h"

#include "JNIHelper.h"


static constexpr const char* ID_FIELD = "id_";
static constexpr const char* ISTRANSPARENT_FIELD = "isTransparent_";
static constexpr const char* LEFTTEXTUREID_FIELD = "leftTextureId_";
static constexpr const char* RIGHTTEXTUREID_FIELD = "rightTextureId_";
static constexpr const char* FRONTTEXTUREID_FIELD = "frontTextureId_";
static constexpr const char* BACKTEXTUREID_FIELD = "backTextureId_";
static constexpr const char* TOPTEXTUREID_FIELD = "topTextureId_";
static constexpr const char* BOTTOMTEXTUREID_FIELD = "bottomTextureId_";

static constexpr const char* ID_SIGNATURE = "I";
static constexpr const char* ISTRANSPARENT_SIGNATURE = "Z";
static constexpr const char* LEFTTEXTUREID_SIGNATURE = "I";
static constexpr const char* RIGHTTEXTUREID_SIGNATURE = "I";
static constexpr const char* FRONTTEXTUREID_SIGNATURE = "I";
static constexpr const char* BACKTEXTUREID_SIGNATURE = "I";
static constexpr const char* TOPTEXTUREID_SIGNATURE = "I";
static constexpr const char* BOTTOMTEXTUREID_SIGNATURE = "I";


namespace conversion {


void Block::construct( JNIEnv* env ) {
	idField_ = JNIHelper::findField( env, ID_FIELD, ID_SIGNATURE );
	isTransparentField_ = JNIHelper::findField( env, ISTRANSPARENT_FIELD, ISTRANSPARENT_SIGNATURE );
	leftTextureIdField_ = JNIHelper::findField( env, LEFTTEXTUREID_FIELD, LEFTTEXTUREID_SIGNATURE );
	rightTextureIdField_ = JNIHelper::findField( env, RIGHTTEXTUREID_FIELD, RIGHTTEXTUREID_SIGNATURE );
	frontTextureIdField_ = JNIHelper::findField( env, FRONTTEXTUREID_FIELD, FRONTTEXTUREID_SIGNATURE );
	backTextureIdField_ = JNIHelper::findField( env, BACKTEXTUREID_FIELD, BACKTEXTUREID_SIGNATURE );
	topTextureIdField_ = JNIHelper::findField( env, TOPTEXTUREID_FIELD, TOPTEXTUREID_SIGNATURE );
	bottomTextureIdField_ = JNIHelper::findField( env, BOTTOMTEXTUREID_FIELD, BOTTOMTEXTUREID_SIGNATURE );
}

void Block::destruct( JNIEnv* env ) {

}

chunk::block::Block Block::cpp_Block( JNIEnv* env, jobject block ) {
	auto id = env->GetIntField( block, idField_ );
	auto isTransparent = env->GetBooleanField( block, isTransparentField_ );
	auto leftTextureId = env->GetIntField( block, leftTextureIdField_ );
	auto rightTextureId = env->GetIntField( block, rightTextureIdField_ );
	auto frontTextureId = env->GetIntField( block, frontTextureIdField_ );
	auto backTextureId = env->GetIntField( block, backTextureIdField_ );
	auto topTextureId = env->GetIntField( block, topTextureIdField_ );
	auto bottomTextureId = env->GetIntField( block, bottomTextureIdField_ );

	return { id, isTransparent, leftTextureId, rightTextureId, frontTextureId, backTextureId, topTextureId, bottomTextureId };
}


}
