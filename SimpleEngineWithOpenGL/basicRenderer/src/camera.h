#pragma once
#include "actor.h"

class Camera : public Actor
{
public :
	Camera();

	void updateActor(float dt) override;
	void actorInput(const Uint8* keys, const Uint32* mouseState, int mousePositionX, int mousePositionY) override;
private:
	class MoveComponent* moveComponent;
};