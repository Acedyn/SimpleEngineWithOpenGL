#pragma once
#include "texture.h"
#include <vector>
#include <string>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void unload();

	class VertexArray* getVertexArray() { return vertexArray; }
	const std::string& getShaderName() { return shaderName; }
	float getRadius() const { return radius; }

	void addTexture(Texture* texture);
	Texture* getTexture(int index);

	void setVertexArray(VertexArray* vertexArrayP);
	void setShaderName(std::string& shaderNameP);
	void setRadius(float radiusP);

private:
	std::vector<Texture*> textures;
	class VertexArray* vertexArray;
	std::string shaderName;
	float radius; 
};