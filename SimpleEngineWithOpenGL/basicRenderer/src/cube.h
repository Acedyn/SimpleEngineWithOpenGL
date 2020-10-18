#pragma once
#include "actor.h"
#include "meshComponent.h"
#include "moveComponent.h"

class Cube : public Actor
{
public:
	Cube();

	void actorInput(const Uint8* keys, const Uint32* mouseState, int mousePositionX, int mousePositionY) override;
	void updateActor(float dt) override;

private:
	MeshComponent* mc;
	MoveComponent* mv;

	bool grabbing;
	Vector2 grabDirection;
	Vector2 mousePosition;
};