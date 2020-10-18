#include "moveComponent.h"
#include "maths.h"
#include "actor.h"
#include "window.h"
#include "log.h"
#include <sstream>

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP),
	forwardSpeed(0.0f),
	sideSpeed(0.0f),
	yawSpeed(0.0f),
	pitchSpeed(0.0f)
{

}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::setSideSpeed(float sideSpeedP)
{
	sideSpeed = sideSpeedP;
}

void MoveComponent::setYawSpeed(float yawSpeedP)
{
	yawSpeed = yawSpeedP;
}

void MoveComponent::setPitchSpeed(float pitchSpeedP)
{
	pitchSpeed = pitchSpeedP;
}

void MoveComponent::update(float dt)
{
	if (!Maths::nearZero(yawSpeed))
	{
		Quaternion newRotation = owner.getRotation();
		float angle = yawSpeed * dt;
		Quaternion increment(Vector3::unitZ, angle);
		newRotation = Quaternion::concatenate(newRotation, increment);
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(pitchSpeed))
	{
		Quaternion newRotation = owner.getRotation();
		float angle = pitchSpeed * dt;
		Quaternion increment(Vector3::unitY, angle);
		newRotation = Quaternion::concatenate(newRotation, increment);
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(forwardSpeed))
	{
		Vector3 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt;
		owner.setPosition(newPosition);
	}
	if (!Maths::nearZero(sideSpeed))
	{
		Vector3 newPosition = owner.getPosition() + owner.getSide() * sideSpeed * dt;
		owner.setPosition(newPosition);
	}
}