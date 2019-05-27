#include "Eventing/KeyEvent.h"


namespace eventing {


const char* to_string( KeyEventType type ) {
	switch ( type ) {
		case KeyEventType::Pressed:
			return "Pressed";
		case KeyEventType::Down:
			return "Down";
		case KeyEventType::Released:
			return "Released";
		default:
			return "<undefined>";
	}
}


}