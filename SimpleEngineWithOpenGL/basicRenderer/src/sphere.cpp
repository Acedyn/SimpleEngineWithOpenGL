#include "sphere.h"
#include "meshComponent.h"
#include "assets.h"

Sphere::Sphere() : Actor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
}