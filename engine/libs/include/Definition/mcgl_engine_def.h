#pragma once

#include <stdint.h>

#include "../Eventing/KeyEvent.h"
#include "../Eventing/MouseEvent.h"
#include "../Eventing/StatusEvent.h"

typedef uint32_t UNUM32;
typedef int32_t NUM32;

// TODO: Remove after config implementation
constexpr unsigned int CHUNK_WIDTH = 16;
constexpr unsigned int CHUNK_LENGTH = 16;
constexpr unsigned int CHUNK_HEIGHT = 128;

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