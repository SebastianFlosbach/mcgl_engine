#include "Chunk.h"

#include <iostream>

#include "JNIHelper.h"
#include "ChunkCoordinates.h"


static constexpr const char* CLASS_NAME = "Chunk";
static constexpr const char* BLOCKS_FIELD = "blocks_";
static constexpr const char* BLOCKS_SIGNATURE = "[[[I";
static constexpr const char* POSITION_FIELD = "position_";
static constexpr const char* POSITION_SIGNATURE = "LChunkCoordinates;";


namespace conversion {


jclass Chunk::clazz_{ nullptr };
jfieldID Chunk::blocksFieldId_{ nullptr };
jfieldID Chunk::positionFieldId_{ nullptr };

void Chunk::construct( JNIEnv* env ) {
	clazz_ = JNIHelper::createClass( env, CLASS_NAME );
	blocksFieldId_ = JNIHelper::findField( env, clazz_, BLOCKS_FIELD, BLOCKS_SIGNATURE );
	positionFieldId_ = JNIHelper::findField( env, clazz_, POSITION_FIELD, POSITION_SIGNATURE );
}

void Chunk::destruct( JNIEnv* env ) {
	if( clazz_ ) {
		JNIHelper::destroyClass( env, clazz_ );
	}
}

chunk::Chunk_ptr Chunk::cpp_Chunk( JNIEnv* env, jobject jChunk ) {
	chunk::Chunk_ptr cppBlocks = std::make_unique<chunk::Chunk>();

	auto jPosition = env->GetObjectField( jChunk, positionFieldId_ );
	auto cppPosition = ChunkCoordinates::cpp_ChunkCoordinates( env, jPosition );

	cppBlocks->setPosition( cppPosition );

	auto d3Blocks = (jobjectArray)env->GetObjectField( jChunk, blocksFieldId_ );

	auto d3Size = env->GetArrayLength( d3Blocks );

	for( size_t x = 0; x < d3Size; x++ ) {
		auto d2Blocks = (jobjectArray)env->GetObjectArrayElement( d3Blocks, x );

		auto d2Size = env->GetArrayLength( d2Blocks );

		for( size_t y = 0; y < d2Size; y++ ) {
			auto d1Blocks = (jintArray)env->GetObjectArrayElement( d2Blocks, y );

			auto d1Size = env->GetArrayLength( d1Blocks );

			auto pBlocks = env->GetIntArrayElements( d1Blocks, nullptr );
			
			for( size_t z = 0; z < d1Size; z++ ) {
				cppBlocks->setBlock( x, y, z, pBlocks[z] );
			}
		}
	}

	return cppBlocks;
}


}