#pragma once
#include "iRenderer.h"
#include "vertexArray.h"
#include "vector2.h"
#include "shader.h"
#include "directionalLight.h"

#include <vector>

class RendererOGL : public IRenderer
{
public:
	RendererOGL();
	virtual ~RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	// Initialization of the renderer called by the game class initialize() function
	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void endDraw();

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const override;
	void addMesh(class MeshComponent* mesh);
	void removeMesh(class MeshComponent* mesh);
	void setViewMatrix(const Matrix4& viewP);

	DirectionalLight& getDirectionalLight() { return dirLight; }

	void setLightUniforms(Shader& shader);
	void setAmbientLight(const Vector3& ambientP);

	void close();
	IRenderer::Type type() { return Type::OGL; }

private:
	void drawSprites();
	void drawMeshes();

	// Pointer to the window class
	Window* window;
	VertexArray* spriteVertexArray;
	SDL_GLContext context;
	Matrix4 spriteViewProj;
	// This is the matrix containing the camera transform
	Matrix4 view;
	// This it the projection matrix
	Matrix4 projection;
	// This is the ambient light intensity and color
	Vector3 ambientLight;
	// Struct containing the direction and the light color infos of the mesh
	DirectionalLight dirLight;

	std::vector<class SpriteComponent*> sprites;
	std::vector<class MeshComponent*> meshes;
};