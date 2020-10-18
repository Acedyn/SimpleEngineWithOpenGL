#pragma once
#include "actor.h"
#include <SDL_stdinc.h>

class Component
{
public:
	Component(Actor* ownerP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }

	virtual void update(float dt);
	virtual void processInput(const Uint8* keyState, const Uint32* mouseState, int mousePositionX, int mousePositionY);
	virtual void onUpdateWorldTransform() {}

protected:
	Actor& owner;
	int updateOrder;
};