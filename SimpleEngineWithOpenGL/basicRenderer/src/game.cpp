#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "meshComponent.h"
#include "Timer.h"
#include "Assets.h"
#include "cube.h"
#include "sphere.h"

bool Game::initialize()
{
	// Initialize the window class
	bool isWindowInit = window.initialize();
	// Initialize the renderer class to the window
	bool isRendererInit = renderer.initialize(window);
	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	// Load the shader and put it in the assets class
	Assets::loadShader("../res/shaders/Sprite.vert", "../res/shaders/Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader("../res/shaders/BasicMesh.vert", "../res/shaders/BasicMesh.frag", "", "", "", "BasicMesh");
	Assets::loadShader("../res/shaders/Phong.vert", "../res/shaders/Phong.frag", "", "", "", "Phong");

	// Load the textures and put it in the assets class
	Assets::loadTexture(renderer, "../res/textures/Default.png", "Default");
	Assets::loadTexture(renderer, "../res/textures/Cube.png", "Cube");
	Assets::loadTexture(renderer, "../res/textures/HealthBar.png", "HealthBar");
	Assets::loadTexture(renderer, "../res/textures/Plane.png", "Plane");
	Assets::loadTexture(renderer, "../res/textures/Radar.png", "Radar");
	Assets::loadTexture(renderer, "../res/textures/Sphere.png", "Sphere");

	// Load the meshes and put it in the assets class
	Assets::loadMesh("../res/meshes/Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh("../res/meshes/Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh("../res/meshes/Sphere.gpmesh", "Mesh_Sphere");

	// Create a camera instance
	camera = new Camera();

	// Create an empty Actor
	Actor* a = new Cube();
	// Set its position to 300, 105, 0
	a->setPosition(Vector3(200.0f, 105.0f, 0.0f));
	// Set its scale to 100
	a->setScale(100.0f);
	// Create a quaternion
	Quaternion q(Vector3::unitY, -Maths::piOver2);
	// Rotate the quaternion
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
	a->setRotation(q);

	// Same for an other Actor
	Actor* b = new Sphere();
	b->setPosition(Vector3(200.0f, -75.0f, 0.0f));
	b->setScale(3.0f);

	// Lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, 0.707f, 0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);
}

void Game::processInput()
{
	// Create and SDL_Event
	SDL_Event event;
	// SDL_PollEvent will check if there is some event waiting to be executed
	// If there is some it will put it in SDL_Event
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// If the event is of type SDL_QUIT
		case SDL_QUIT:
			// Stop the game
			isRunning = false;
			break;
		}
	}
	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		// Give to the actor the keyboard state
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::update(float dt)
{
	// Update actors 
	isUpdatingActors = true;
	for(auto actor: actors) 
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor: pendingActors)
	{
		pendingActor->computeWorldTransform();
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	std::vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}
