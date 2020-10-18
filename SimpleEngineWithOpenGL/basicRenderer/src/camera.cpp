#include "camera.h"
#include "moveComponent.h"
#include "game.h"

Camera::Camera() : Actor(), moveComponent(nullptr)
{
	moveComponent = new MoveComponent(this);
}

void Camera::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);

	// Compute new camera from this actor
	Vector3 cameraPos = getPosition();
	Vector3 target = getPosition() + getForward() * 100.0f;
	Vector3 up = Vector3::unitZ;

	Matrix4 view = Matrix4::createLookAt(cameraPos, target, up);
	getGame().getRenderer().setViewMatrix(view);
}

void Camera::actorInput(const Uint8* keys, const Uint32* mouseState, int mousePositionX, int mousePositionY)
{
	float forwardSpeed = 0.0f;
	float sideSpeed = 0.0f;
	float yawSpeed = 0.0f;
	float pitchSpeed = 0.0f;
	// wasd movement
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		sideSpeed -= 300.0f;
	}
	if (keys[SDL_SCANCODE_D])
	{
		sideSpeed += 300.0f;
	}
	/*if (keys[SDL_SCANCODE_UP])
	{
		pitchSpeed -= Maths::twoPi;
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		pitchSpeed += Maths::twoPi;
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		yawSpeed -= Maths::twoPi;
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		yawSpeed += Maths::twoPi;
	}*/

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setSideSpeed(sideSpeed);
	moveComponent->setYawSpeed(yawSpeed);
	moveComponent->setPitchSpeed(pitchSpeed);
}