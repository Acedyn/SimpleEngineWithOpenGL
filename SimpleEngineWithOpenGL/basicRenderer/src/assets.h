#pragma once
#include "texture.h"
#include "shader.h"
#include "mesh.h"
#include <string>
#include <map>

// A static singleton Asset class that hosts several functions to load resources.
class Assets
{
public:
	// Static map containing all the textures
	static std::map <std::string, Texture> textures;
	// Static map containing all the shaders
	static std::map <std::string, Shader> shaders;
	// Static map containing all the meshes
	static std::map <std::string, Mesh> meshes;

	// Called by Game::load() to call loadTextureFromFile() and stores it to the textures map
	static Texture loadTexture(IRenderer& renderer, const std::string fileName, const std::string& name);
	// Check if the asked texture exists in the textures map and return it
	static Texture& getTexture(const std::string& name);

	// Called by Game::load() to call loadShaderFromFile() and stores it to the shaders map
	static Shader loadShader(const std::string& vShaderFile, 
		const std::string& fShaderFile,
		const std::string& tcShaderFile, 
		const std::string& teShaderFile,
		const std::string& gShaderFile, 
		const std::string& name);
	// Check if the asked shader exists in the shaders map and return it
	static Shader& getShader(const std::string& name);

	// Called by Game::load() to call loadMeshFromFile() and stores it to the meshes map
	static Mesh loadMesh(const std::string& fileName, const std::string& name);
	// Check if the asked meshe exists in the meshs map and return it
	static Mesh& getMesh(const std::string& name);

	static void clear();

private:
	Assets() {}

	// Called by loadTexture() to load the given files into an OpenGL texture
	static Texture loadTextureFromFile(IRenderer& renderer, const std::string& fileName);

	// Called by loadShader() to load the given files into a OpenGL shader
	static Shader loadShaderFromFile(const std::string& vShaderFile, 
		const std::string& fShaderFile,
		const std::string& tcShaderFile = "", 
		const std::string& teShaderFile = "",
		const std::string& gShaderFile = "");

	// Called by loadMesh() to load the given files into a OpenGL mesh
	static Mesh loadMeshFromFile(const std::string& filename);
};