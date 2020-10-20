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

	if (mouseButton == 1)
	{
		Vector2 currentMousePosition(static_cast<float>(mousePositionX), static_cast<float>(mousePositionY));
		if (grabbing)
		{
			grabDirection = mousePosition - currentMousePosition;
		}
		mousePosition = currentMousePosition;
		grabbing = 1;
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