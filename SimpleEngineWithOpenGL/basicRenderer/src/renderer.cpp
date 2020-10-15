#include "renderer.h"
#include "log.h"
#include "texture.h"
#include "maths.h"
#include "spriteComponent.h"
#include <SDL_image.h>

Renderer::Renderer() : SDLRenderer(nullptr)
{

}

bool Renderer::initialize(Window& window)
{
	SDLRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLRenderer)
	{
		Log::error(LogCategory::Video, "Failed to create renderer");
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::error(LogCategory::Video, "Unable to initialize SDL_image");
		return false;
	}
	return true;
}

void Renderer::beginDraw()
{
	SDL_SetRenderDrawColor(SDLRenderer, 5, 15, 30, 255);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::endDraw()
{
	SDL_RenderPresent(SDLRenderer);
}

void Renderer::draw()
{
	drawSprites();
}

void Renderer::drawRect(const Rectangle& rect) const
{
	SDL_SetRenderDrawColor(SDLRenderer, 0, 255, 0, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

void Renderer::close()
{
	SDL_DestroyRenderer(SDLRenderer);
}

// Query for drawing all the sprites of the sprite array
void Renderer::drawSprites()
{
	for (auto sprite : sprites)
	{
		sprite->draw(*this);
	}
}

// Draw the given srite
void Renderer::drawSprite(const Actor& actor, const class Texture& texture, Rectangle srcRect, Vector2 origin, Flip flip) const
{
	// Create an SDL_rect and get the actor's transfrom
	SDL_Rect dstRect;
	Vector2 position = actor.getPosition();
	float rotation = actor.getRotation();
	float scale = actor.getScale();

	// Set the SDL_rect width according the the actor transform
	dstRect.w = static_cast<int>(texture.getWidth() * scale);
	dstRect.h = static_cast<int>(texture.getHeight() * scale);
	dstRect.x = static_cast<int>(position.x - origin.x);
	dstRect.y = static_cast<int>(position.y - origin.y);

	
	SDL_Rect* srcSDL = nullptr;
	if (srcRect != Rectangle::nullRect)
	{
		srcSDL = new SDL_Rect{
			Maths::round(srcRect.x),
			Maths::round(srcRect.y),
			Maths::round(srcRect.width),
			Maths::round(srcRect.height)
		};
	}
	// Apply the texture to to rect
	SDL_RenderCopyEx(
		SDLRenderer,
		texture.toSDLTexture(),
		srcSDL,
		&dstRect,
		-rotation,
		nullptr,
		SDL_FLIP_NONE);
}

void Renderer::addSprite(SpriteComponent* sprite)
{
	int spriteDrawOrder = sprite->getDrawOrder();
	auto iter = std::begin(sprites);
	for (; iter != std::end(sprites); ++iter)
	{
		if (spriteDrawOrder < (*iter)->getDrawOrder())
		{
			break;
		}
	}
	sprites.insert(iter, sprite);
}

void Renderer::removeSprite(SpriteComponent* sprite)
{
	auto iter = std::find(std::begin(sprites), std::end(sprites), sprite);
	sprites.erase(iter);
}