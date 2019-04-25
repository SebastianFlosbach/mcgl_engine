#pragma once

#include <map>
#include <memory>

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

typedef std::unique_ptr<BlockLibrary> BlockLibrary_ptr;
typedef std::shared_ptr<BlockLibrary> BlockLibrary_sptr;

}
}