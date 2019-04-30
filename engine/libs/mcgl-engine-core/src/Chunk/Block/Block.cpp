#include "Chunk/Block/Block.h"


namespace chunk {
namespace block {


Block::Block( const Block& other ) :
	id_( other.id_ ),
	isTransparent_( other.isTransparent_ ),
	leftTextureId_( other.leftTextureId_ ),
	rightTextureId_( other.rightTextureId_ ),
	frontTextureId_( other.frontTextureId_ ),
	backTextureId_( other.backTextureId_ ),
	topTextureId_( other.topTextureId_ ),
	bottomTextureId_( other.bottomTextureId_ )
{}

Block& Block::operator=( const Block& other ) {
	if( this == &other ) {
		return *this;
	}

	return Block( other );
}


}
}
