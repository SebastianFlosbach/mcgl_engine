#pragma once


namespace eventing {


struct PositionData {
	PositionData( const double x, const double y ) : x_( x ), y_( y ) {};

	const double x_;
	const double y_;
};

struct ButtonData {
	ButtonData( int button, double timePressed ) : button_( button ), timePressed_( timePressed ) {};

	const int button_;
	const double timePressed_;
};

enum class MouseEventType {
	ButtonPess,
	ButtonRelease,
	Scroll,
	Move
};

struct MouseEvent {
	MouseEvent( MouseEventType type, double x, double y ) : type_( type ), data_( x, y ) {}
	MouseEvent( MouseEventType type, int button, double timePressed ) : type_( type ), data_( button, timePressed ) {}


	MouseEventType type_;

	union MouseEventData {
		MouseEventData( double x, double y ) : position_( x, y ) {};
		MouseEventData( int button, double timePressed ) : button_( button, timePressed ) {};

		PositionData position_;
		ButtonData button_;
	} data_;
};

const char* to_string( MouseEventType type );


}
