#pragma once

enum class StatusEventType {
	Running,
	Stopped
};

struct StatusEvent {
	StatusEventType type_;
};