#pragma once
#include "component.h"
class MoveComponent : public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrder = 10); // By default, update before other components
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	float getForwardSpeed() const { return forwardSpeed; }
	float getSideSpeed() const { return sideSpeed; }
	float getYawSpeed() const { return yawSpeed; }
	float getPitchSpeed() const { return pitchSpeed; }

	void setForwardSpeed(float forwardSpeedP);
	void setSideSpeed(float sideSpeedP);
	void setYawSpeed(float yawSpeedP);
	void setPitchSpeed(float pitchSpeedP);

	void update(float dt) override;


private:
	float forwardSpeed;
	float sideSpeed;
	float yawSpeed;
	float pitchSpeed;
};