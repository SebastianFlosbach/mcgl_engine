#pragma once

#include "../Eventing/KeyEvent.h"
#include "../Eventing/MouseEvent.h"

typedef void( *MCGL_KEY_EVENT_CALLBACK )(const KeyEvent&); 
typedef void(*MCGL_MOUSE_EVENT_CALLBACK)(const MouseEvent&);