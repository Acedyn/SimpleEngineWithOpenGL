#pragma once
#include <vector>
#include "vector2.h"
#include "vector3.h"
#include "quaternion.h"
#include "matrix4.h"
#include <SDL_stdinc.h>

class Game;
class Component;

class Actor
{
public:
	enum class ActorState
	{
		Active, Paused, Dead
	};

	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector3 getPosition() const { return position; }
	const float getScale() const { return scale; }
	const Quaternion getRotation() const { return rotation; }
	const Matrix4& getWorldTransform() const { return worldTransform; }

	void setState(ActorState stateP);
	void setPosition(Vector3 positionP);
	void setScale(float scaleP);
	void setRotation(Quaternion rotationP);

	void update(float dt);
	void updateComponent(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);
	void computeWorldTransform();

	// Call the processInput of all the components
	void processInput(const Uint8* keyState, const Uint32* mouseState, int mousePositionX, int mousePositionY);
	virtual void actorInput(const Uint8* keys, const Uint32* mouseState, int mousePositionX, int mousePositionY);

	Vector3 getForward() const;
	Vector3 getSide() const;

private:
	Game& game;
	ActorState state;
	Vector3 position;
	float scale;
	Quaternion rotation;
	Matrix4 worldTransform;
	bool mustRecomputeWorldTransform;

	std::vector<Component*> components;
};