#include "World/Block/BlockLibrary.h"

namespace world {
namespace block {


void BlockLibrary::addBlock( Block block, unsigned int id ) {
	if ( blockMap_.find( id ) != blockMap_.end() ) {
		return;
	}

	blockMap_.insert( { id, block } );
}

const Block& BlockLibrary::getBlock( unsigned int id ) const {
	return blockMap_.find( id )->second;
}


}
}