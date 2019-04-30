#pragma once


namespace chunk {
namespace block {


/**
	Contains data about a type of block
*/
struct Block {
	/**
		Generate a new type of block
		\param id Block id
		\param isTransparent Is this block transparent, if true the following arguments have no effect
		\param leftTextureId Texture id for the left side texture
		\param rightTextureId Texture id for the right side texture
		\param frontTextureId Texture id for the front side texture
		\param backTextureId Texture id for the back side texture
		\param topTextureId Texture id for the top texture
		\param bottomTextureId Texture id for the bottom texture
	*/
	Block(
		const UNUM32 id,
		const bool isTransparent,
		const UNUM32 leftTextureId = 0,
		const UNUM32 rightTextureId = 0,
		const UNUM32 frontTextureId = 0,
		const UNUM32 backTextureId = 0,
		const UNUM32 topTextureId = 0,
		const UNUM32 bottomTextureId = 0
	) : id_( id ),
		isTransparent_( isTransparent ),
		leftTextureId_( leftTextureId ),
		rightTextureId_( rightTextureId ),
		frontTextureId_( frontTextureId ),
		backTextureId_( backTextureId ),
		topTextureId_( topTextureId ),
		bottomTextureId_( bottomTextureId )
	{}

	Block( const Block& other );
	Block& operator=( const Block& other );

	const UNUM32 id_;
	const bool isTransparent_;
	const UNUM32 leftTextureId_;
	const UNUM32 rightTextureId_;
	const UNUM32 frontTextureId_;
	const UNUM32 backTextureId_;
	const UNUM32 topTextureId_;
	const UNUM32 bottomTextureId_;
};


}
}