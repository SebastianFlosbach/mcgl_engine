#pragma once

#include <map>

#include "Block.h"

namespace world {
namespace block {


class BlockLibrary {
public:
	BlockLibrary() = default;

	void addBlock( Block block, unsigned int id );

	const Block& getBlock( unsigned int id ) const;

private:
	std::map<unsigned int, Block> blockMap_;

};


}
}