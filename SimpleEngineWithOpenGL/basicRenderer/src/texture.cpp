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
	else
	{
		glDeleteTextures(1, &textureID);
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

bool Texture::loadOGL(RendererOGL& rendererP, const std::string& fileNameP)
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

	int format = 0;
	if (surf->format->format == SDL_PIXELFORMAT_RGBA32)
	{
		format = GL_RGBA;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, surf->pixels);
	SDL_FreeSurface(surf);

	Log::info("Loaded texture " + fileName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

void Texture::updateInfo(int& widthOut, int& heightOut)
{
	widthOut = width;
	heightOut = height;
}