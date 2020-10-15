#pragma once
#include "rendererSDL.h"
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool load(RendererSDL& rendererP, const std::string& fileNameP);
	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
	std::string getName() const { return fileName; }

private:
	std::string fileName;
	SDL_Texture* SDLTexture;
	int width;
	int height;
};