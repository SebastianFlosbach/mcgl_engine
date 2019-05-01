#pragma once

#include "Definition/mcgl_engine_def.h"


namespace coordinates {
struct ChunkCoordinates;
struct WorldCoordinates;

struct BlockCoordinates {
public:
	BlockCoordinates( NUM32 x, NUM32 y, NUM32 z );

	ChunkCoordinates toChunkCoordinates() const;

	WorldCoordinates toWorldCoordinates() const;

	NUM32 x_, y_, z_;
};


}