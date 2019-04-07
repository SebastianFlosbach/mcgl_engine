#pragma once

namespace action {


enum class ActionType {
	ACreateWindow,
};

struct Action {
public:
	virtual ActionType type() const = 0;

};


}