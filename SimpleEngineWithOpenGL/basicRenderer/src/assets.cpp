#include "assets.h"
#include "log.h"
#include "rapidjson/document.h"
#include <sstream>
#include <fstream>

// Forward declaration of the static maps contraining the textures, shaders, meshes
std::map<std::string, Texture> Assets::textures;
std::map<std::string, Shader> Assets::shaders;
std::map<std::string, Mesh> Assets::meshes;


Texture Assets::loadTexture(IRenderer& renderer, const std::string fileName, const std::string& name)
{
    // Call the function that actualy load the texture and stores if the the textures map
	textures[name] = loadTextureFromFile(renderer, fileName.c_str());
	return textures[name];
}

Texture& Assets::getTexture(const std::string& name)
{
    // If the given name is found in the shaders map
	if (textures.find(name) == end(textures))
	{
        // Log error
		std::ostringstream loadError;
		loadError << "Texture" << name << "does not exist in asset manager.";
		Log::error(LogCategory::Application, loadError.str());
	}
	return textures[name];
}

Shader Assets::loadShader(const std::string& vShaderFile, 
	const std::string& fShaderFile, 
	const std::string& tcShaderFile, 
	const std::string& teShaderFile, 
	const std::string& gShaderFile, 
	const std::string& name)
{
    // Call the function that actualy load the shader and stores if the the shader map
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, tcShaderFile, teShaderFile, gShaderFile);
	return shaders[name];
}

Shader& Assets::getShader(const std::string& name)
{
    // If the given name is found in the shaders map
	if (shaders.find(name) == end(shaders))
	{
        // Log error
		std::ostringstream loadError;
		loadError << "Shader " << name << " does not exist in assets manager.";
		Log::error(LogCategory::Application, loadError.str());
	}
	return shaders[name];
}

Mesh Assets::loadMesh(const std::string& fileName, const std::string& name)
{
    // Call the function that actualy load the mesh and stores if the the shader map
    meshes[name] = loadMeshFromFile(fileName);
    return meshes[name];
}

Mesh& Assets::getMesh(const std::string& name)
{
    // If the given name is found in the shaders map
    if (meshes.find(name) == std::end(meshes))
    {
        // Log error
        std::ostringstream loadError;
        loadError << "Mesh " << name << " does not exist in asset manager";
        Log::error(LogCategory::Application, loadError.str());
    }
    return meshes[name];
}

void Assets::clear()
{
	for (auto iter : textures)
	{
		iter.second.unload();
	}
	textures.clear();
    for (auto iter : shaders)
    {
        iter.second.unload();
    }
	shaders.clear();
    for (auto iter : meshes)
    {
        iter.second.unload();
    }
    meshes.clear();

}

Texture Assets::loadTextureFromFile(IRenderer& renderer, const std::string& fileName)
{
    // Create a texture instance
    Texture texture; 
    // Load the file into the created texture
    texture.loadOGL(dynamic_cast<RendererOGL&>(renderer), fileName);

    return texture;
}

Shader Assets::loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& tcShaderFile, const std::string& teShaderFile, const std::string& gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string tcCode;
    std::string teCode;
    std::string geometryCode;
    try {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If tess control shader path is present, also load a tess control shader
        if (tcShaderFile != "") {
            std::ifstream tessControlShaderFile(tcShaderFile);
            std::stringstream tcShaderStream;
            tcShaderStream << tessControlShaderFile.rdbuf();
            tessControlShaderFile.close();
            tcCode = tcShaderStream.str();
        }
        // If tess evaluation shader path is present, also load a tess evaluation shader
        if (teShaderFile != "") {
            std::ifstream tessEvalShaderFile(teShaderFile);
            std::stringstream teShaderStream;
            teShaderStream << tessEvalShaderFile.rdbuf();
            tessEvalShaderFile.close();
            teCode = teShaderStream.str();
        }
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != "") {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::ostringstream loadError;
        std::string geomShaderFile = "";
        if (gShaderFile != "")
            geomShaderFile = gShaderFile;

        loadError << "ERROR::SHADER: Failed to read shader files " << vShaderFile << " " << fShaderFile << " "
            << geomShaderFile << "\n"
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
        Log::error(LogCategory::Render, loadError.str());
    }
    // Create GLchar that will contain the code
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    const GLchar* tcShaderCode = tcCode.c_str();
    const GLchar* teShaderCode = teCode.c_str();
    const GLchar* gShaderCode = geometryCode.c_str();

    // 2. Now create shader object from source code
    Shader shader;
    shader.compile(vShaderCode, fShaderCode,
        tcShaderFile != "" ? tcShaderCode : nullptr,
        teShaderFile != "" ? teShaderCode : nullptr,
        gShaderFile != "" ? gShaderCode : nullptr);
    return shader;
}

Mesh Assets::loadMeshFromFile(const std::string& fileName)
{
    // Create an empty mesh instance
    Mesh mesh;

    // Read the content of the file at the given path
    std::ifstream file(fileName);
    // If the file is not found
    if (!file.is_open())
    {
        // Log error
        Log::error(LogCategory::Application, "File not found: Mesh " + fileName);
    }
    // Store the content of the file in a string
    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    // Store the string to a rapidjson string
    rapidjson::StringStream jsonStr(contents.c_str());
    // Create an empty json formatted object
    rapidjson::Document doc;
    // Interpret the content of the file and stores it in doc
    doc.ParseStream(jsonStr);

    // If the interpretation went wrong
    if (!doc.IsObject())
    {
        // Log error
        std::ostringstream s;
        s << "Mesh " << fileName << " is not valid json";
        Log::error(LogCategory::Application, s.str());
    }
    // Give to the mesh the name of its shader from the json file
    mesh.setShaderName(doc["shader"].GetString());

    // This variable is responsible for the amount of data in byte in each vertex
    // 3 bytes for XYZ, 3 bytes for normals and 2 bytes for UV
    size_t vertSize = 8;

    // Load textures
    // Get the content of "textures" from the json file
    const rapidjson::Value& textures = doc["textures"];
    // If there is no textures found
    if (!textures.IsArray() || textures.Size() < 1)
    {
        // Log error
        std::ostringstream s;
        s << "Mesh " << fileName << " has no textures, there should be at least one";
        Log::error(LogCategory::Application, s.str());
    }
    mesh.setSpecularPower(static_cast<float>(doc["specularPower"].GetDouble()));

    // For each textures in the "textures" part of the json file
    for (rapidjson::SizeType i = 0; i < textures.Size(); i++)
    {
        // Get the name and try to find it in the textures in Assets
        std::string texName = textures[i].GetString();
        Texture& t = getTexture(texName);
        // Link the found texture to the mesh
        mesh.addTexture(&t);
    }

    // Load in the vertices
    const rapidjson::Value& vertsJson = doc["vertices"];
    // If no vertices found
    if (!vertsJson.IsArray() || vertsJson.Size() < 1)
    {
        // Log error
        std::ostringstream s;
        s << "Mesh " << fileName << " has no vertices";
        Log::error(LogCategory::Application, s.str());
    }
    // Create an empty verctor that will contain all the vertices
    std::vector<float> vertices;
    // Pre allocate memory for the vertices
    vertices.reserve(vertsJson.Size() * vertSize);
    // Initialize the radius of the mesh (for collision i guess)
    // Depracated
    float radius = 0.0f;
    // For each vertice of the vertices section of the json file
    for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
    {
        // For now, just assume we have 8 elements
        const rapidjson::Value& vert = vertsJson[i];
        // If the vertex does not contain 8 value (x, y, z, normalX, normalY, normalZ, u, v)
        if (!vert.IsArray() || vert.Size() != 8)
        {
            // Log error
            std::ostringstream s;
            s << "Unexpected vertex format for " << fileName;
            Log::error(LogCategory::Application, s.str());
        }
        // Create a vector3 that will contain the x, y, z values
        // Deprecated since we are not using position infos anymore
        Vector3 pos(static_cast<float>(vert[0].GetDouble()), static_cast<float>(vert[1].GetDouble()), static_cast<float>(vert[2].GetDouble()));
        // Set the radius
        // Deprecated
        radius = Maths::max(radius, pos.lengthSq());

        // Add the floats of each 8 value of the vertice
        for (rapidjson::SizeType i = 0; i < vert.Size(); i++)
        {
            vertices.emplace_back(static_cast<float>(vert[i].GetDouble()));
        }
    }

    // We were computing length squared earlier
    // Depracated
    mesh.setRadius(Maths::sqrt(radius));

    // Load in the indices from the json file
    const rapidjson::Value& indJson = doc["indices"];
    // If the "indices" section is empty or don't exists
    if (!indJson.IsArray() || indJson.Size() < 1)
    {
        // Log error
        std::ostringstream s;
        s << "Mesh " << fileName << " has no indices";
        Log::error(LogCategory::Application, s.str());
    }
    // Create an empty vector to store all the indices
    std::vector<unsigned int> indices;
    // Pre allocate the memory for the indices vector
    indices.reserve(indJson.Size() * 3.0);
    // For each indices
    for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
    {
        // Get the values of the indice
        const rapidjson::Value& ind = indJson[i];
        // If there isn't 3 value in the indice
        if (!ind.IsArray() || ind.Size() != 3)
        {
            // Log error
            std::ostringstream s;
            s << "Invalid indices for " << fileName;
            Log::error(LogCategory::Application, s.str());
        }
        // Add the values of the indice to the vector indices
        indices.emplace_back(ind[0].GetUint());
        indices.emplace_back(ind[1].GetUint());
        indices.emplace_back(ind[2].GetUint());
    }

    // Now create a vertex array witch :
    // our vertices, 
    // the amount of vertices so it knows how much infos per vertices
    // the indices wich link the vertices to form triangles
    // the amount of indices so it knows how much infos per indices (in out case 3 since its triangles)
    mesh.setVertexArray(new VertexArray(
        vertices.data(), 
        static_cast<unsigned int>(vertices.size()) / vertSize, 
        indices.data(), 
        static_cast<unsigned int>(indices.size())));

    Log::info("Loaded mesh " + fileName);

    return mesh;
}