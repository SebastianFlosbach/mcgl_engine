#pragma once
#include <tuple>

enum class MouseEventType {
	ButtonPess,
	ButtonRelease,
	Scroll,
	MouseMove
};

struct MouseEvent {
	MouseEvent( MouseEventType type, double xOffset, double yOffset ) : type_( type ), data_( xOffset, yOffset ) {}
	MouseEvent( MouseEventType type, int button, double timePressed ) : type_( type ), data_( button, timePressed ) {}
	MouseEvent( MouseEventType type, int xPos, int yPos ) : type_( type ), data_( xPos, yPos ) {}


	MouseEventType type_;

	union MouseEventData {
		MouseEventData( double xOffset, double yOffset ) : scroll_( xOffset, yOffset ) {}
		MouseEventData( int button, double timePressed ) : button_( button, timePressed ) {}
		MouseEventData( int xPos, int yPos ) : mouse_( xPos, yPos ) {}

		std::tuple<double, double> scroll_;
		std::tuple<int, double> button_;
		std::tuple<int, int> mouse_;
	} data_;
};

const char* to_string( MouseEventType type );