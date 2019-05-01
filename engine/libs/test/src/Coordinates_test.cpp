#include <gtest/gtest.h>

#include <Coordinates/BlockCoordinates.h>
#include <Coordinates/ChunkCoordinates.h>
#include <Coordinates/WorldCoordinates.h>

using namespace coordinates;


TEST( Coordinates_test, BlockCoordinates_Construction ) {
	const int x = 1;
	const int y = 2;
	const int z = 3;

	BlockCoordinates blockCoordinates = BlockCoordinates( x, y, z );

	ASSERT_EQ( blockCoordinates.x_, x );
	ASSERT_EQ( blockCoordinates.y_, y );
	ASSERT_EQ( blockCoordinates.z_, z );
}

TEST( Coordinates_test, ChunkCoordinates_Construction ) {
	const int x = 1;
	const int z = 2;

	ChunkCoordinates chunkCoordinates = ChunkCoordinates( x, z );

	ASSERT_EQ( chunkCoordinates.x_, x );
	ASSERT_EQ( chunkCoordinates.z_, z );
}

TEST( Coordinates_test, WorldCoordinates_Construction ) {
	const float x = 1.0f;
	const float y = 2.1f;
	const float z = 3.2f;

	WorldCoordinates worldCoordinates = WorldCoordinates( x, y, z );

	ASSERT_EQ( worldCoordinates.x_, x );
	ASSERT_EQ( worldCoordinates.y_, y );
	ASSERT_EQ( worldCoordinates.z_, z );
}

TEST( Coordinates_test, Convert_Block_To_Chunk ) {
	BlockCoordinates blockCoordinates = BlockCoordinates( 0, 0, 0 );
	ChunkCoordinates chunkCoordinates = blockCoordinates.toChunkCoordinates();
	ASSERT_EQ( chunkCoordinates.x_, 0 );
	ASSERT_EQ( chunkCoordinates.z_, 0 );

	blockCoordinates = BlockCoordinates( 0, 1, 0 );
	chunkCoordinates = blockCoordinates.toChunkCoordinates();
	ASSERT_EQ( chunkCoordinates.x_, 0 );
	ASSERT_EQ( chunkCoordinates.z_, 0 );

	blockCoordinates = BlockCoordinates( 15, 0, 0 );
	chunkCoordinates = blockCoordinates.toChunkCoordinates();
	ASSERT_EQ( chunkCoordinates.x_, 0 );
	ASSERT_EQ( chunkCoordinates.z_, 0 );

	blockCoordinates = BlockCoordinates( 16, 0, 0 );
	chunkCoordinates = blockCoordinates.toChunkCoordinates();
	ASSERT_EQ( chunkCoordinates.x_, 1 );
	ASSERT_EQ( chunkCoordinates.z_, 0 );

	blockCoordinates = BlockCoordinates( -1, 0, 0 );
	chunkCoordinates = blockCoordinates.toChunkCoordinates();
	ASSERT_EQ( chunkCoordinates.x_, -1 );
	ASSERT_EQ( chunkCoordinates.z_, 0 );

	blockCoordinates = BlockCoordinates( -16, 0, 0 );
	chunkCoordinates = blockCoordinates.toChunkCoordinates();
	ASSERT_EQ( chunkCoordinates.x_, -1 );
	ASSERT_EQ( chunkCoordinates.z_, 0 );

	blockCoordinates = BlockCoordinates( -17, 0, 0 );
	chunkCoordinates = blockCoordinates.toChunkCoordinates();
	ASSERT_EQ( chunkCoordinates.x_, -2 );
	ASSERT_EQ( chunkCoordinates.z_, 0 );
}

// TODO: Finish tests
TEST( Coordinates_test, Convert_Block_To_World ) {

}

TEST( Coordinates_test, Convert_Chunk_To_Block ) {

}

TEST( Coordinates_test, Convert_Chunk_To_World ) {

}

TEST( Coordinates_test, Convert_World_To_Block ) {

}

TEST( Coordinates_test, Convert_World_To_Chunk ) {

}
