#pragma once
#include"rectangle.h"
#include"window.h"
#include "actor.h"
#include "iRenderer.h"
#include<SDL.h>

class RendererSDL : public IRenderer
{
public:
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

	RendererSDL();
	RendererSDL(const RendererSDL&) = delete;
	RendererSDL& operator=(const RendererSDL&) = delete;

	bool initialize(Window& window) override;

	void beginDraw() override;
	void draw() override;
	void drawRect(const Rectangle& rect) const;
	void endDraw() override;
	void close() override;

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprites();
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;

	inline SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }
	IRenderer::Type type() override { return IRenderer::Type::SDL; }

private:
	SDL_Renderer* SDLRenderer = nullptr;
	std::vector<SpriteComponent*> sprites;
};