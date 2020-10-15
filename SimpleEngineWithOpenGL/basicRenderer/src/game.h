#pragma once
#include "window.h"
#include "RendererSDL.h"
#include "vector2.h"
#include "actor.h"
#include "timer.h"
#include "spriteComponent.h"
#include <vector>

class Game
{
public:
	// Singleton function to create the game
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() :
		isRunning(true),
		isUpdatingActors(false)
	{};

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	RendererSDL& getRenderer() { return renderer; }
	void addActor(Actor* actor);
	void removeActor(Actor* actor);

private:
	void processInput();
	void update(float dt);
	void render();

	Window window;
	RendererSDL renderer;
	bool isRunning;

	bool isUpdatingActors;
	std::vector<Actor*>  actors;
	std::vector<Actor*> pendingActors;


};
