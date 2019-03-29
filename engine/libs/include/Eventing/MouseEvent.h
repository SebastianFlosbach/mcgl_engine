#pragma once
#include <tuple>

enum class MouseEventType {
	ButtonPess,
	ButtonRelease,
	Scroll,
	MouseMove
};

struct MouseEvent {
	MouseEventType type_;

	union MouseEventData {
		std::tuple<double, double> scroll_;
		std::tuple<int, double> button_;
		std::tuple<int, int> mouse_;
	} data_;
};

const std::string to_string( MouseEventType type ) {
	switch ( type ) {
		case MouseEventType::ButtonPess:
			return "ButtonPress";
		case MouseEventType::ButtonRelease:
			return "ButtonRelease";
		case MouseEventType::Scroll:
			return "Scroll";
		case MouseEventType::MouseMove:
			return "MouseMove";
		default:
			return "<undefined>";
	}
}