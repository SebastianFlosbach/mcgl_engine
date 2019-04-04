#pragma once

#include <stdint.h>

#include "../Eventing/KeyEvent.h"
#include "../Eventing/MouseEvent.h"
#include "../Eventing/StatusEvent.h"

typedef uint32_t UNUM32;
typedef int32_t NUM32;

typedef void( *MCGL_KEY_EVENT_CALLBACK )(const KeyEvent&); 
typedef void( *MCGL_MOUSE_EVENT_CALLBACK )(const MouseEvent&);
typedef void( *MCGL_STATUS_EVENT_CALLBACK )(const StatusEvent&);