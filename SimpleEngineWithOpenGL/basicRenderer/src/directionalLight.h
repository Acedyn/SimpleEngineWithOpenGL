#pragma once
#include "vector3.h"

struct DirectionalLight
{
	DirectionalLight(Vector3 directionP, Vector3 diffuseColorP, Vector3 specColorP) :
		direction(directionP),
		diffuseColor(diffuseColorP),
		specColor(specColorP) {}
	Vector3 direction;
	Vector3 diffuseColor;
	Vector3 specColor;
};