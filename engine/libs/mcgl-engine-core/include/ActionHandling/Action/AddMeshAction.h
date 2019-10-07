#pragma once

#include "Action.h"

#include "World/Mesh/IMesh.h"
#include "Coordinates/WorldCoordinates.h"


namespace action {


struct AddMeshAction : public Action {
public:
	AddMeshAction( world::mesh::IMesh_ptr&& mesh ) : pMesh_( std::move( mesh ) ) {}

	ActionType type() const override { return ActionType::AddMeshAction; }

	world::mesh::IMesh_ptr pMesh_;

};


}
