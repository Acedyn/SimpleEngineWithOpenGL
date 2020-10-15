#include "spriteComponent.h"
#include "actor.h"
#include "game.h"

// Contructor also query to its owner to add it to its component array
SpriteComponent::SpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP) :
	Component(ownerP),
	texture(textureP),
	drawOrder(drawOrderP),
	texWidth(textureP.getWidth()),
	texHeight(textureP.getHeight())
{
	owner.getGame().getRenderer().addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	owner.getGame().getRenderer().removeSprite(this);
}

void SpriteComponent::setTexture(const Texture& textureP)
{
	texture = textureP;
	texture.updateInfo(texWidth, texHeight);
}

// Query drawing this sprite to the renderer
void SpriteComponent::draw(RendererSDL& renderer)
{
	Vector2 origin{ texWidth / 2.0f, texHeight / 2.0f };
	renderer.drawSprite(owner, texture, Rectangle::nullRect, origin, RendererSDL::Flip::None);
}