#pragma once

#include <memory>


namespace action {


	enum class ActionType {
		AddChunkAction,
		AddMeshAction,
		CloseWindowAction,
		CreateCameraAction,
		CreateWindowAction,
		DrawAction,
		EngineInitAction,
		GetDeltaTimeAction,
		MoveCameraAction,
		RegisterBlockTypeAction,
		RegisterKeyEventCallbackAction,
		RegisterMouseEventCallbackAction,
		RegisterStatusEventCallbackAction,
		RemoveChunkAction,
		RotateCameraAction,
		RunAction,
		SetShaderAction,
		SetTexturesAction,
		StopAction,
	};

	const char* to_string( const ActionType type );

	struct Action {
	public:
		virtual ActionType type() const = 0;

	};

	typedef std::unique_ptr<Action> Action_ptr;

}