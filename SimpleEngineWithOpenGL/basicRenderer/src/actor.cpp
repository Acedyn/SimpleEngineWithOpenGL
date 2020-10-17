#include "actor.h"
#include "game.h"
#include "component.h"
#include "maths.h"
#include <algorithm>

Actor::Actor() :
	state(Actor::ActorState::Active),
	position(Vector3::zero),
	scale(1.0f),
	rotation(Quaternion::identity),
	mustRecomputeWorldTransform(true),
	game(Game::instance())
{
	game.addActor(this);
}

// Call all components destructors and ask to the game to remove it from the actors array
Actor::~Actor()
{
	game.removeActor(this);
	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::setState(ActorState stateP)
{
	state = stateP;
}

void Actor::setPosition(Vector3 positionP)
{
	position = positionP;
	mustRecomputeWorldTransform = true;
}

void Actor::setScale(float scaleP)
{
	scale = scaleP;
	mustRecomputeWorldTransform = true;
}

void Actor::setRotation(Quaternion rotationP)
{
	rotation = rotationP;
	mustRecomputeWorldTransform = true;
}

void Actor::update(float dt)
{
	if (state == Actor::ActorState::Active)
	{
		computeWorldTransform();
		updateComponent(dt);
		updateActor(dt);
		computeWorldTransform();
	}
}

void Actor::updateComponent(float dt)
{
	for (auto component : components)
	{
		component->update(dt);
	}
}

void Actor::updateActor(float dt)
{

}

// Add a component to the component array. Called by the component constructor
void Actor::addComponent(Component* component)
{
	int componentOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (componentOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	components.insert(iter, component);
}

// Remove a component to the component array. Called by the component destructor
void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}

Vector3 Actor::getForward() const
{
	return Vector3::transform(Vector3::unitX, rotation);
}

void Actor::processInput(const Uint8* keyState)
{
	// If the actor is active
	if (state == Actor::ActorState::Active)
	{
		// For each components
		for (auto component : components)
		{
			// Call process input
			component->processInput(keyState);
		}
		actorInput(keyState);
	}
}

void Actor::computeWorldTransform()
{
	if (mustRecomputeWorldTransform)
	{
		mustRecomputeWorldTransform = false;
		worldTransform = Matrix4::createScale(scale);
		worldTransform *= Matrix4::createFromQuaternion(rotation);
		worldTransform *= Matrix4::createTranslation(position);

		for (auto component : components)
		{
			component->onUpdateWorldTransform();
		}
	}
}

void Actor::actorInput(const Uint8* keyState) {}