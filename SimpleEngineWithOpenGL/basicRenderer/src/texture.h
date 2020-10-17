#pragma once
#include "rendererOGL.h"
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	// Called by Assets::loadTextureFromFile to create a OpenGL texture
	bool loadOGL(RendererOGL& rendererP, const std::string& filenameP);
	void updateInfo(int& widthOut, int& heightOut);
	// Bind the texture so it will be the one that OpenGL will use
	void setActive() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	std::string fileName;
	SDL_Texture* SDLTexture = nullptr;
	int width;
	int height;
	unsigned int textureID;
};