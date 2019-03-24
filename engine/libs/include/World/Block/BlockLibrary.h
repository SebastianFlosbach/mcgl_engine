#pragma once

#include <map>

#include "Block.h"

namespace world {
namespace block {


class BlockLibrary {
public:
	BlockLibrary() = default;

	void addBlock( Block block, unsigned int id ) {
		if ( blockMap_.find( id ) != blockMap_.end() ) {
			return;
		}

		blockMap_.insert( { id, block } );
	}

	const Block& getBlock( unsigned int id ) const {
		return blockMap_.find( id )->second;
	}

private:
	std::map<unsigned int, Block> blockMap_;

};


}
}