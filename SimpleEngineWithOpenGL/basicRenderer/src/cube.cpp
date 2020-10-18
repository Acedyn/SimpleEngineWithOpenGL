#include "cube.h"
#include "assets.h"
#include "log.h"
#include "game.h"
#include "camera.h"
#include "maths.h"
#include <sstream>
#include "log.h"
#include "matrix4.h"
#include "vector2.h"

Cube::Cube() :
	Actor(),
	mc(nullptr),
	mv(nullptr),
	grabbing(false),
	grabDirection(Vector2(0, 0)),
	mousePosition(Vector2(0, 0))
{
	mv = new MoveComponent(this);
	mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
}

void Cube::actorInput(const Uint8* keys, const Uint32* mouseState, int mousePositionX, int mousePositionY)
{
	int mouseButton = static_cast<int>(*mouseState);
	float forwardSpeed = 0.0f;
	float sideSpeed = 0.0f;
	float yawSpeed = 0.0f;
	float pitchSpeed = 0.0f;
	// wasd movement
	/*if (keys[SDL_SCANCODE_W])
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
	}*/
	if (keys[SDL_SCANCODE_UP])
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
	}


	if (mouseButton == 1)
	{
		Vector2 currentMousePosition(static_cast<float>(mousePositionX), static_cast<float>(mousePositionY));
		if (grabbing)
		{
			grabDirection = mousePosition - currentMousePosition;
		}
		mousePosition = currentMousePosition;
		grabbing = 1;
		std::ostringstream logInfo;
		logInfo << "currentMousePosition : " << currentMousePosition.x << " " << currentMousePosition.y;
		logInfo << " - mousePosition : " << mousePosition.x << " " << mousePosition.y;
		logInfo << " = grabDirection : " << grabDirection.x << " " << grabDirection.y;
		Log::info(logInfo.str());
	}
	else
	{
		grabbing = false;
	}

}

void Cube::updateActor(float dt)
{
	Quaternion cameraRotation = getGame().getCamera()->getRotation();
	Vector3 grabRotation = Vector3::transform(Vector3(0, grabDirection.y, grabDirection.x), cameraRotation);
	grabRotation.normalize();
	float rotationSpeed = grabDirection.lenght()*0.2;
	mv->setArbitraryAngleSpeed(grabRotation, rotationSpeed);

}