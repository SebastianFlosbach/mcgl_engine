#include "FieldIDCache.h"

#include <exception>
#include <sstream>

#include "ClassDefinitions.h"


namespace conversion{


jfieldID FieldIDCache::GetBlockId( JNIEnv* env ) {
	if( !blockId_ ) {
		jclass clazz = env->FindClass( CLASS_BLOCK );

		blockId_ = env->GetFieldID( clazz, BLOCK_ID_FIELD, BLOCK_ID_SIGNATURE );
		if( !blockId_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not get field '" << BLOCK_ID_FIELD << "' of class '" << CLASS_BLOCK << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return blockId_;
}

jfieldID FieldIDCache::GetIsTransparent( JNIEnv* env ) {
	if( !blockIsTransparent_ ) {
		jclass clazz = env->FindClass( CLASS_BLOCK );

		blockIsTransparent_ = env->GetFieldID( clazz, BLOCK_ISTRANSPARENT_FIELD, BLOCK_ISTRANSPARENT_SIGNATURE );
		if( !blockIsTransparent_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not get field '" << BLOCK_ISTRANSPARENT_FIELD << "' of class '" << CLASS_BLOCK << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return blockIsTransparent_;
}

jfieldID FieldIDCache::GetLeftTextureId( JNIEnv* env ) {
	if( !blockLeftTextureId_ ) {
		jclass clazz = env->FindClass( CLASS_BLOCK );

		blockLeftTextureId_ = env->GetFieldID( clazz, BLOCK_LEFTTEXTUREID_FIELD, BLOCK_LEFTTEXTUREID_SIGNATURE );
		if( !blockLeftTextureId_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not get field '" << BLOCK_LEFTTEXTUREID_FIELD << "' of class '" << CLASS_BLOCK << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return blockLeftTextureId_;
}

jfieldID FieldIDCache::GetRightTextureId( JNIEnv* env ) {
	if( !blockRightTextureId_ ) {
		jclass clazz = env->FindClass( CLASS_BLOCK );

		blockRightTextureId_ = env->GetFieldID( clazz, BLOCK_RIGHTTEXTUREID_FIELD, BLOCK_RIGHTTEXTUREID_SIGNATURE );
		if( !blockRightTextureId_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not get field '" << BLOCK_RIGHTTEXTUREID_FIELD << "' of class '" << CLASS_BLOCK << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return blockRightTextureId_;
}

jfieldID FieldIDCache::GetTopTextureId( JNIEnv* env ) {
	if( !blockTopTextureId_ ) {
		jclass clazz = env->FindClass( CLASS_BLOCK );

		blockTopTextureId_ = env->GetFieldID( clazz, BLOCK_TOPTEXTUREID_FIELD, BLOCK_TOPTEXTUREID_SIGNATURE );
		if( !blockTopTextureId_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not get field '" << BLOCK_TOPTEXTUREID_FIELD << "' of class '" << CLASS_BLOCK << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return blockTopTextureId_;
}

jfieldID FieldIDCache::GetBottomTextureId( JNIEnv* env ) {
	if( !blockBottomTextureId_ ) {
		jclass clazz = env->FindClass( CLASS_BLOCK );

		blockBottomTextureId_ = env->GetFieldID( clazz, BLOCK_BOTTOMTEXTUREID_FIELD, BLOCK_BOTTOMTEXTUREID_SIGNATURE );
		if( !blockBottomTextureId_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not get field '" << BLOCK_BOTTOMTEXTUREID_FIELD << "' of class '" << CLASS_BLOCK << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return blockBottomTextureId_;
}

jfieldID FieldIDCache::GetFrontTextureId( JNIEnv* env ) {
	if( !blockFrontTextureId_ ) {
		jclass clazz = env->FindClass( CLASS_BLOCK );

		blockFrontTextureId_ = env->GetFieldID( clazz, BLOCK_FRONTTEXTUREID_FIELD, BLOCK_FRONTTEXTUREID_SIGNATURE );
		if( !blockFrontTextureId_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not get field '" << BLOCK_FRONTTEXTUREID_FIELD << "' of class '" << CLASS_BLOCK << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return blockFrontTextureId_;
}

jfieldID FieldIDCache::GetBackTextureId( JNIEnv* env ) {
	if( !blockBackTextureId_ ) {
		jclass clazz = env->FindClass( CLASS_BLOCK );

		blockBackTextureId_ = env->GetFieldID( clazz, BLOCK_BACKTEXTUREID_FIELD, BLOCK_BACKTEXTUREID_SIGNATURE );
		if( !blockBackTextureId_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not get field '" << BLOCK_BACKTEXTUREID_FIELD << "' of class '" << CLASS_BLOCK << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return blockBackTextureId_;
}

jfieldID FieldIDCache::GetKeyEventType( JNIEnv* env, const char* name ) {
	if( !keyEventType_ ) {
		auto clazz = env->FindClass( ENUM_KEYEVENTTYPE );

		keyEventType_ = env->GetStaticFieldID( clazz, name, KEYEVENTTYPE_SIGNATURE );
		if( !keyEventType_ ) {
			std::stringstream errorMsg;
			errorMsg << __FUNCTION__ << ": Could not get static field '" << name << "' of enum '" << ENUM_KEYEVENTTYPE << "'!";
			throw std::runtime_error( errorMsg.str() );
		}
	}

	return keyEventType_;
}

}
