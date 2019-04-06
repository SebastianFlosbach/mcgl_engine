#pragma once

enum class ActionType {
	CreateEngine,
	CreateWindow,
	Run,
	DestroyEngine,
};

struct Action {
public:
	virtual ActionType getType() const = 0;

};