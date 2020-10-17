#pragma once
#include "actor.h"
#include "meshComponent.h"
#include "moveComponent.h"

class Cube : public Actor
{
public:
	Cube();

	void actorInput(const Uint8* keys) override;

private:
	MeshComponent* mc;
	MoveComponent* mv;
};