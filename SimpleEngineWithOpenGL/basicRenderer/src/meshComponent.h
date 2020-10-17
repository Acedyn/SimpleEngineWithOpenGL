#pragma once
#include "component.h"

class MeshComponent : public Component
{
public:
	MeshComponent(Actor* owner);
	virtual ~MeshComponent();

	// Called by the renderer to draw its content
	virtual void draw(class Shader& shader);
	virtual void setMesh(class Mesh& meshP);
	void setTextureIndex(size_t textureIndexP);

protected:
	Mesh* mesh;
	size_t textureIndex;
};