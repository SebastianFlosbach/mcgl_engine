#pragma once


struct ChunkCoordinates {
	ChunkCoordinates( int x, int z ) : x_( x ), z_( z ) {}

	ChunkCoordinates( const ChunkCoordinates& other ) noexcept {
		if( this == &other ) {
			return;
		}

		x_ = other.x_;
		z_ = other.z_;
	}

	ChunkCoordinates& operator=( const ChunkCoordinates& other ) noexcept {
		return other;
	}

	int x_, z_;
};


namespace std {

template<>
struct hash<ChunkCoordinates> {
	size_t operator()( const ChunkCoordinates& ChunkCoordinates ) const noexcept {
		int x, z;

		if( ChunkCoordinates.x_ >= 0 ) {
			x = ChunkCoordinates.x_ * 2;
		}
		else {
			x = -ChunkCoordinates.x_ * 2 - 1;
		}

		if( ChunkCoordinates.z_ >= 0 ) {
			z = ChunkCoordinates.z_ * 2;
		}
		else {
			z = -ChunkCoordinates.z_ * 2 - 1;
		}

		return ((x + z) * (x + z + 1) / 2) * z;
	}
};

template<>
struct equal_to<ChunkCoordinates> {
	constexpr bool operator()( const ChunkCoordinates& left, const ChunkCoordinates& right ) const {	// apply operator== to operands
		return left.x_ == right.x_ && left.z_ == right.z_;
	}
};

}