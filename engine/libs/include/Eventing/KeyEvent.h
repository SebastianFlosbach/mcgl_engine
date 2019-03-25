#pragma once

enum class KeyEventType {
	Pressed,
	Down,
	Released
};

struct KeyEvent {
	KeyEventType type_;
	int key_;
	double timePressed_;
};

const char* to_string( KeyEventType type ) {
	switch ( type ) {
		case KeyEventType::Pressed:
			return "Pressed";
		case KeyEventType::Down:
			return "Down";
		case KeyEventType::Released:
			return "Released";
		default:
			return "<unknown>";
	}
}