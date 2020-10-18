#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "camera.h"

class Game
{
public:
	// This static function calls the constructor, since it is static it will return always the same instance
	static Game& instance()
	{

		static Game inst;
		return inst;
	}

	// Delete the assign and copy operator
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	Camera* getCamera() { return camera; }

private:
	// The constructor is private so only the instance() function can call it
	Game() : isRunning(true), isUpdatingActors(false), camera(nullptr) {}

public:

	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	RendererOGL& getRenderer() { return renderer; }


private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	// Window class that will be initialized at the begining
	Window window;
	// Renderer class that will be initialize at he begining
	RendererOGL renderer;
	Camera* camera;

	bool isUpdatingActors;
	std::vector<Actor*> actors;
	std::vector<Actor*> pendingActors;

};

