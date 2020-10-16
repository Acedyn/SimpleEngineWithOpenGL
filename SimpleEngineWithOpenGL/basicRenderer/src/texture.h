#pragma once
#include "rendererOGL.h"
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool loadOGL(RendererOGL& rendererP, const std::string& filenameP);
	//inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);
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