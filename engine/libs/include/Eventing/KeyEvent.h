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