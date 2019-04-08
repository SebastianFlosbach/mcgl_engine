#pragma once

#include <memory>


namespace action {


enum class ActionType;

struct ActionData {
public:
	virtual ActionType type() const = 0;



};

typedef std::unique_ptr<ActionData> ActionData_ptr;


}