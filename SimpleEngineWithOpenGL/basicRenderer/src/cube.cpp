#include "cube.h"
#include "assets.h"

Cube::Cube() : 
	Actor(),
	mc(nullptr),
	mv(nullptr)
{
	mv = new MoveComponent(this);
	mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
}

void Cube::actorInput(const Uint8* keys)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (keys[SDL_SCANCODE_UP])
	{
		forwardSpeed += 300.0f;
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		forwardSpeed -= 300.0f;
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		angularSpeed -= Maths::twoPi;
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		angularSpeed += Maths::twoPi;
	}

	mv->setForwardSpeed(forwardSpeed);
	mv->setAngularSpeed(angularSpeed);
}