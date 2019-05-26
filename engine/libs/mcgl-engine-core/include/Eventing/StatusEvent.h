#pragma once


namespace eventing {


enum class StatusEventType {
	Running,
	Stopped
};

struct StatusEvent {
	StatusEventType type_;
};


}