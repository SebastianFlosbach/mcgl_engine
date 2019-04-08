#pragma once

#include "ActionData.h"

namespace action {


enum class ActionType {
	CreateWindowAction,
	RunAction,
	StopAction,
	SetShaderAction,
};

struct Action {
public:
	Action( ActionType type, ActionData_ptr&& data ) : type_( type ), data_( std::move( data ) ) {}

	Action( ActionType type ) : type_( type ) {}

	virtual ActionType type() const { return type_; }
	ActionData* data() const { return data_.get(); }

private:
	ActionType type_;
	ActionData_ptr data_;

};


}