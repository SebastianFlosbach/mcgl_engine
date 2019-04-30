#pragma once

#include <stdint.h>

#include "../Eventing/KeyEvent.h"
#include "../Eventing/MouseEvent.h"
#include "../Eventing/StatusEvent.h"

typedef uint32_t UNUM32;
typedef int32_t NUM32;

constexpr UNUM32 UNUM32_MAX = UINT32_MAX;
constexpr NUM32 NUM32_MAX = INT32_MAX;

// TODO: Remove after config implementation
constexpr UNUM32 CHUNK_WIDTH = 16; /** Chunk width in blocks in x direction */
constexpr UNUM32 CHUNK_LENGTH = 16; /** Chunk length in blocks in z direction */
constexpr UNUM32 CHUNK_HEIGHT = 128; /** Chunk height in blocks in y direction */

constexpr float BLOCK_SIZE = 1.0f;
constexpr NUM32 BLOCK_DEFAULT_ID = 0;

typedef void( *MCGL_KEY_EVENT_CALLBACK )(const KeyEvent&); 
typedef void( *MCGL_MOUSE_EVENT_CALLBACK )(const MouseEvent&);
typedef void( *MCGL_STATUS_EVENT_CALLBACK )(const StatusEvent&);

enum class MCGL_CONFIG {
	BLOCK_SIZE,
	CHUNK_WIDTH,
	CHUNK_HEIGHT,
	CHUNK_LENGTH,
	FRAMERATE,
};
