#include "texture.h"
#include "log.h"
#include <SDL_image.h>

Texture::Texture() :
	fileName(""),
	width(0),
	height(0),
	SDLTexture(nullptr) {}

Texture::~Texture() {}

void Texture::unload()
{
	if (SDLTexture)
	{
		SDL_DestroyTexture(SDLTexture);
	}
}

// Create the SDL_Surface and create a texture from it to the renderer
bool Texture::loadSDL(RendererSDL& rendererP, const std::string& fileNameP)
{
	fileName = fileNameP;
	SDL_Surface* surf = IMG_Load(fileName.c_str());
	if (!surf)
	{
		Log::error(LogCategory::Application, "Failed to load texture file " + fileName);
		return false;
	}
	width = surf->w;
	height = surf->h;

	SDLTexture = SDL_CreateTextureFromSurface(rendererP.toSDLRenderer(), surf);
	SDL_FreeSurface(surf);
	if (!SDLTexture)
	{
		Log::error(LogCategory::Render, "Failed to convert to texture for " + fileName);
		return false;
	}
	Log::info("Loaded texture" + fileName);

	return true;
}

void Texture::updateInfo(int& widthOut, int& heightOut)
{
	widthOut = width;
	heightOut = height;
}