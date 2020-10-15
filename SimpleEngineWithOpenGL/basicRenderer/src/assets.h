#pragma once
#include "texture.h"
#include "shader.h"
#include <string>
#include <map>

// A static singleton Asset class that hosts several
// functions to load resources.
class Assets
{
public:
	static std::map <std::string, Texture> textures;
	static std::map <std::string, Shader> shaders;

	static Texture loadTexture(IRenderer& renderer, const std::string fileName, const std::string& name);
	static Texture& getTexture(const std::string& name);

	static Shader loadShader(const std::string& vShaderFile, 
		const std::string& fShaderFile,
		const std::string& tcShaderFile, 
		const std::string& teShaderFile,
		const std::string& gShaderFile, 
		const std::string& name);
	static Shader& getShader(const std::string& name);

	static void clear();

private:
	Assets() {}

	static Texture loadTextureFromFile(IRenderer& renderer, const std::string& fileName);

	static Shader loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile,
		const std::string& tcShaderFile = "", const std::string& teShaderFile = "",
		const std::string& gShaderFile = "");
};