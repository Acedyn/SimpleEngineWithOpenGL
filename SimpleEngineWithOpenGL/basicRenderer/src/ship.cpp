#include "ship.h"
#include "spriteComponent.h"
#include "assets.h"
#include "maths.h"

Ship::Ship() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("ship"));
}

void Ship::actorInput(const Uint8* keyState)
{
}

void Ship::updateActor(float dt)
{
	laserCoolDown -= dt;
}