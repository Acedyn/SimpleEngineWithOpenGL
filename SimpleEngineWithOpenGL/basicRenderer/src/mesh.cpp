#include "mesh.h"
#include "vertexArray.h"

// Constructor initialize the values
Mesh::Mesh() :
	vertexArray(nullptr),
	shaderName(""),
	radius(0.0f) {}

Mesh::~Mesh() {}

void Mesh::unload()
{
	delete vertexArray;
	vertexArray = nullptr;
}

Texture* Mesh::getTexture(int index)
{
	if (index < textures.size())
	{
		return textures[index];
	}
	else
	{
		return nullptr;
	}
}

void Mesh::setVertexArray(VertexArray* vertexArrayP)
{
	vertexArray = vertexArrayP;
}

void Mesh::setRadius(float radiusP)
{
	radius = radiusP;
}