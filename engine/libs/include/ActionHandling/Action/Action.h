#pragma once

#include <memory>


namespace action {


enum class ActionType {
	CreateWindowAction,
	CloseWindowAction,
	RunAction,
	StopAction,
	SetShaderAction,
};

struct Action {
public:
	virtual ActionType type() const = 0;

};

typedef std::unique_ptr<Action> Action_ptr;

}