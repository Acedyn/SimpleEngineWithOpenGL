#include "component.h"

// Contructor also query to its owner to add it to its component array
Component::Component(Actor* ownerP, int updateOrderP) :
	owner(*ownerP),
	updateOrder(updateOrderP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::update(float dt)
{

}

void Component::processInput(const Uint8* keyState, const Uint32* mouseState, int mousePositionX, int mousePositionY) {}
