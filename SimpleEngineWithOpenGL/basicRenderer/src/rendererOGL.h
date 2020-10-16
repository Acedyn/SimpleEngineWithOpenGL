#pragma once
#include "iRenderer.h"
#include "vertexArray.h"
#include "vector2.h"
#include "shader.h"

#include <vector>

class RendererOGL : public IRenderer
{
public:
	RendererOGL();
	virtual ~RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void endDraw();

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const override;

	void close();
	IRenderer::Type type() { return Type::OGL; }

private:
	void drawSprites();
	Shader* shader;

	Matrix4 viewProj;

	Window* window;
	VertexArray* vertexArray;
	SDL_GLContext context;
	std::vector<class SpriteComponent*> sprites;
};