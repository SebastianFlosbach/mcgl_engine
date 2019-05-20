#include "Eventing/MouseEvent.h"

const char* to_string( MouseEventType type ) {
	switch ( type ) {
		case MouseEventType::ButtonPess:
			return "ButtonPress";
		case MouseEventType::ButtonRelease:
			return "ButtonRelease";
		case MouseEventType::Scroll:
			return "Scroll";
		case MouseEventType::Move:
			return "Move";
		default:
			return "<undefined>";
	}
}