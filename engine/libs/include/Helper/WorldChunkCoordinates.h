#pragma once

#include "Definition/mcgl_engine_def.h"


struct ChunkCoordinates {
	ChunkCoordinates( int x, int z ) : x_( x ), z_( z ) {}

	ChunkCoordinates( const ChunkCoordinates& other ) noexcept {
		*this = other;
	}

	ChunkCoordinates& operator=( const ChunkCoordinates& other ) noexcept {
		if( this == &other ) {
			return *this;
		}

		x_ = other.x_;
		z_ = other.z_;

		return *this;
	}

	int x_, z_;
};

struct WorldCoordinates {
	WorldCoordinates( int x, int y, int z ) : x_( x ), y_( y ), z_( z ) {}

	WorldCoordinates( const WorldCoordinates& other ) noexcept {
		*this = other;
	}

	WorldCoordinates& operator=( const WorldCoordinates& other ) noexcept {
		if( this == &other ) {
			return *this;
		}

		x_ = other.x_;
		y_ = other.y_;
		z_ = other.z_;

		return *this;
	}

	int x_, y_, z_;
};

ChunkCoordinates toChunkCoordinates( const WorldCoordinates& worldCoords );
WorldCoordinates toWorldCoordinates( const ChunkCoordinates& chunkCoords );