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