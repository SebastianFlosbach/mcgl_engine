#pragma once

#include <map>
#include <memory>

#include "Block.h"
#include "Definition/mcgl_engine_def.h"


namespace chunk {
namespace block {

/**
	A library for block types
*/
class BlockLibrary {
public:
	BlockLibrary() = default;

	/**
		Register a new type of block.
		If the block is already registered, the current block is overwritten.
		\param block Block to register
	*/
	void registerBlock( const Block& block ) noexcept;

	/**
		Delete a type of block.
		\param id Id of the block to delete
	*/
	void deleteBlock( UNUM32 id ) noexcept;

	/**
		Get a block type from the library.
		If the id is not registered, a default block is returned.
		\param id Id of the block
	*/
	const Block& getBlock( UNUM32 id ) const;

private:
	std::map<UNUM32, Block> blockMap_;

};

typedef std::unique_ptr<BlockLibrary> BlockLibrary_ptr;
typedef std::shared_ptr<BlockLibrary> BlockLibrary_sptr;

}
}