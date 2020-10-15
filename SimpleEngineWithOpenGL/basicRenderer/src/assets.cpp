#include "assets.h"
#include "log.h"
#include <sstream>

std::map<std::string, Texture> Assets::textures;

// Query the texture loading to the renderer and add it to the texture map
Texture Assets::loadTexture(Renderer& renderer, const std::string fileName, const std::string& name)
{
	textures[name] = loadTextureFromFile(renderer, fileName.c_str());
	return textures[name];
}

Texture& Assets::getTexture(const std::string& name)
{
	if (textures.find(name) == end(textures))
	{
		std::ostringstream loadError;
		loadError << "Texture" << name << "does not exist in asset manager.";
		Log::error(LogCategory::Application, loadError.str());
	}
	return textures[name];
}

void Assets::clear()
{
	for (auto iter : textures)
	{
		iter.second.unload();
	}
	textures.clear();
}

// Create a texture and link it to the renderer
Texture Assets::loadTextureFromFile(Renderer& renderer, const std::string& fileName)
{
	Texture texture;
	texture.load(renderer, fileName);
	return texture;
}