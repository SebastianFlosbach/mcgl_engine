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

const char* to_string( KeyEventType type );