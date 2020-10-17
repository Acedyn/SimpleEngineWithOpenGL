#include "meshComponent.h"
#include "actor.h"
#include "game.h"
#include "mesh.h"

MeshComponent::MeshComponent(Actor* owner) :
	Component(owner),
	mesh(nullptr),
	textureIndex(0)
{
	owner->getGame().getRenderer().addMesh(this);
}

MeshComponent::~MeshComponent()
{
	owner.getGame().getRenderer().removeMesh(this);
}

void MeshComponent::draw(Shader& shader)
{
	if (mesh)
	{
		// Get the transform matrix of the actor
		Matrix4 wt = owner.getWorldTransform();
		// Create a uniform variable that will contain the actor transform
		shader.setMatrix4("uWorldTransform", wt);
		// Get the texture of the mesh
		Texture* t = mesh->getTexture(textureIndex);
		// If there is a texture
		if (t)
		{
			// Bind the texture so it will be the one used by OpenGL
			t->setActive();
		}
		// Get the vertexArray of the mesh
		VertexArray* va = mesh->getVertexArray();
		// Bind the vertexArray so it will be the one used by OpenGL
		va->setActive();
		// Ask to OpenGL to draw the binded vertexArray and use the binded texture
		glDrawElements(GL_TRIANGLES, va->getNbIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void MeshComponent::setMesh(Mesh& meshP)
{
	mesh = &meshP;
}

void MeshComponent::setTextureIndex(size_t textureIndexP)
{
	textureIndex = textureIndexP;
}