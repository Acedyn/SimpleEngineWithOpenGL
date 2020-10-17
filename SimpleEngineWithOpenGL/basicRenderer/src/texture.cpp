#include "texture.h"
#include "log.h"
#include <SDL_image.h>

Texture::Texture() :
	fileName(""),
	width(0),
	height(0),
	SDLTexture(nullptr),
	textureID(NULL) {}

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

bool Texture::loadOGL(RendererOGL& rendererP, const std::string& fileNameP)
{
	fileName = fileNameP;
	// Create a SDL_Surface from the given path
	SDL_Surface* surf = IMG_Load(fileName.c_str());
	// If loading the file was unsuccesfull
	if (!surf)
	{
		// Log error
		Log::error(LogCategory::Application, "Failed to load texture file " + fileName);
		return false;
	}
	// Get the width and height in pixel of the image
	width = surf->w;
	height = surf->h;

	int format = 0;
	// If the format of the pixel id RGB24 (i guess 24 bit)
	if (surf->format->format == SDL_PIXELFORMAT_RGB24)
	{
		format = GL_RGB;
	}
	// If the format of the pixel id RGB24 (i guess 32 bit)
	else if (surf->format->format == SDL_PIXELFORMAT_RGBA32)
	{
		format = GL_RGBA;
	}
	// Generate an empty texture and store its id in textureID
	glGenTextures(1, &textureID);
	// Give to the created texture the type GL_TEXTURE_2D
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Assign the pixels of the SDL_Surface to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, surf->pixels);
	// Free the memory of the SDL_Surface object
	SDL_FreeSurface(surf);

	Log::info("Loaded texture " + fileName);

	// Voodoo functions :
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

void Texture::updateInfo(int& widthOut, int& heightOut)
{
	widthOut = width;
	heightOut = height;
}

void Texture::setActive() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}