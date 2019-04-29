#pragma once


struct BlockCoordinates {
	BlockCoordinates( int x, int y, int z ) : x_( x ), y_( y ), z_( z ) {}

	BlockCoordinates( const BlockCoordinates& other ) noexcept {
		*this = other;
	}

	BlockCoordinates& operator=( const BlockCoordinates& other ) noexcept {
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