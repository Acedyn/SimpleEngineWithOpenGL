#pragma once
#include "texture.h"
#include <string>
#include <map>

// A static singleton Asset class that hosts several
// functions to load resources.
class Assets
{
public:
	static std::map <std::string, Texture> textures;

	static Texture loadTexture(Renderer& renderer, const std::string fileName, const std::string& name);
	static Texture& getTexture(const std::string& name);
	static void clear();

private:
	Assets() {}

	static Texture loadTextureFromFile(Renderer& renderer, const std::string& fileName);
};