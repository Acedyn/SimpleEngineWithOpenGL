#include "cube.h"
#include "meshComponent.h"
#include "assets.h"

Cube::Cube() : Actor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
}