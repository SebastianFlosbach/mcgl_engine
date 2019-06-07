#pragma once

#include "Action.h"

#include "Mesh/TexturedMesh.h"
#include "Coordinates/WorldCoordinates.h"


namespace action {


struct AddMeshAction : public Action {
public:
	AddMeshAction( const coordinates::WorldCoordinates& position, mesh::TexturedMesh_ptr&& mesh ) : position_( position ), pMesh_( std::move( mesh ) ) {}

	ActionType type() const override { return ActionType::AddMeshAction; }

	coordinates::WorldCoordinates position_;
	mesh::TexturedMesh_ptr pMesh_;

};


}
