#include "World/Mesh/Chunk/Block/BlockLibrary.h"


namespace world {
	namespace mesh {
		namespace chunk {
			namespace block {


void BlockLibrary::registerBlock( const Block& block ) noexcept {
	auto it = blockMap_.find( block.id_ );
	if( it != blockMap_.end() ) {
		it->second = block;
		return;
	}

	blockMap_.insert( { block.id_, block } );
}

const Block& BlockLibrary::getBlock( UNUM32 id ) const {
	auto it = blockMap_.find( id );

	if( it == blockMap_.end() ) {
		return { id, true };
	}

	return it->second;
}


}
}
	}
}
