#include "ActionHandling/Action/Action.h"

namespace action {


const char* to_string( const ActionType type ) {
	switch( type ) {
	case ActionType::AddChunkAction:
		return "AddChunkAction";
	case ActionType::CloseWindowAction:
		return "CloseWindowAction";
	case ActionType::CreateCameraAction:
		return "CreateCameraAction";
	case ActionType::CreateWindowAction:
		return "CreateWindowAction";
	case ActionType::DrawAction:
		return "DrawAction";
	case ActionType::EngineInitAction:
		return "EngineInitAction";
	case ActionType::GetDeltaTimeAction:
		return "GetDeltaTimeAction";
	case ActionType::MoveCameraAction:
		return "MoveCameraAction";
	case ActionType::RegisterBlockTypeAction:
		return "RegisterBlockTypeAction";
	case ActionType::RegisterKeyEventCallbackAction:
		return "RegisterKeyEventCallbackAction";
	case ActionType::RegisterMouseEventCallbackAction:
		return "RegisterMouseEventCallback";
	case ActionType::RegisterStatusEventCallbackAction:
		return "RegisterStatusCallbackAction";
	case ActionType::RemoveChunkAction:
		return "RemoveChunkAction";
	case ActionType::RotateCameraAction:
		return "RotateCameraAction";
	case ActionType::RunAction:
		return "RunAction";
	case ActionType::SetShaderAction:
		return "SetShaderAction";
	//case ActionType::SetTexturesAction:
	//	return "SetTexturesAction";
	case ActionType::StopAction:
		return "StopAction";
	default:
		return "<undefined>";
	}
}


}