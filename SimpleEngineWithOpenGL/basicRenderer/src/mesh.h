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

	// Add the texture to the textures vector
	void addTexture(Texture* texture){ textures.emplace_back(texture); }
	Texture* getTexture(int index);

	void setVertexArray(VertexArray* vertexArrayP);
	// Set the shader name, the shader need to be loaded in Assets before
	void setShaderName(const std::string& shaderNameP) { shaderName = shaderNameP; }
	void setRadius(float radiusP);

	float getSpecularPower() const { return specularPower; }
	void setSpecularPower(float specularPowerP);

private:
	// Stores all the textures of this mesh
	std::vector<Texture*> textures;
	class VertexArray* vertexArray;
	std::string shaderName;
	float radius; 
	// This value set the intensity of the specular
	float specularPower;
};