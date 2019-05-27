#include "Block.h"

#include "JNIHelper.h"

static constexpr const char* CLASS_NAME = "Block";

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


jclass Block::clazz_{ nullptr };
jfieldID Block::idField_{ nullptr };
jfieldID Block::isTransparentField_{ nullptr };
jfieldID Block::leftTextureIdField_{ nullptr };
jfieldID Block::rightTextureIdField_{ nullptr };
jfieldID Block::frontTextureIdField_{ nullptr };
jfieldID Block::backTextureIdField_{ nullptr };
jfieldID Block::topTextureIdField_{ nullptr };
jfieldID Block::bottomTextureIdField_{ nullptr };

void Block::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
	idField_ = JNIHelper::findField( env, clazz_, ID_FIELD, ID_SIGNATURE );
	isTransparentField_ = JNIHelper::findField( env, clazz_, ISTRANSPARENT_FIELD, ISTRANSPARENT_SIGNATURE );
	leftTextureIdField_ = JNIHelper::findField( env, clazz_, LEFTTEXTUREID_FIELD, LEFTTEXTUREID_SIGNATURE );
	rightTextureIdField_ = JNIHelper::findField( env, clazz_, RIGHTTEXTUREID_FIELD, RIGHTTEXTUREID_SIGNATURE );
	frontTextureIdField_ = JNIHelper::findField( env, clazz_, FRONTTEXTUREID_FIELD, FRONTTEXTUREID_SIGNATURE );
	backTextureIdField_ = JNIHelper::findField( env, clazz_, BACKTEXTUREID_FIELD, BACKTEXTUREID_SIGNATURE );
	topTextureIdField_ = JNIHelper::findField( env, clazz_, TOPTEXTUREID_FIELD, TOPTEXTUREID_SIGNATURE );
	bottomTextureIdField_ = JNIHelper::findField( env, clazz_, BOTTOMTEXTUREID_FIELD, BOTTOMTEXTUREID_SIGNATURE );
}

void Block::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

chunk::block::Block Block::cpp_Block( JNIEnv* env, jobject block ) {
	auto id =				static_cast<UNUM32>( env->GetIntField( block, idField_ ) );
	auto isTransparent =	static_cast<bool>( env->GetBooleanField( block, isTransparentField_ ) );
	auto leftTextureId =	static_cast<UNUM32>( env->GetIntField( block, leftTextureIdField_ ) );
	auto rightTextureId =	static_cast<UNUM32>( env->GetIntField( block, rightTextureIdField_ ) );
	auto frontTextureId =	static_cast<UNUM32>( env->GetIntField( block, frontTextureIdField_ ) );
	auto backTextureId =	static_cast<UNUM32>( env->GetIntField( block, backTextureIdField_ ) );
	auto topTextureId =		static_cast<UNUM32>( env->GetIntField( block, topTextureIdField_ ) );
	auto bottomTextureId =	static_cast<UNUM32>( env->GetIntField( block, bottomTextureIdField_ ) );

	return { id, isTransparent, leftTextureId, rightTextureId, frontTextureId, backTextureId, topTextureId, bottomTextureId };
}


}
