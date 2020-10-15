#include"game.h"

int main(int argc, char** argv)
{
	bool isGameInit = Game::instance().initialize();
	if (isGameInit)
	{
		// Load all the textures
		Game::instance().load();
		// Loop the game
		Game::instance().loop();
		// Unload all the textures
		Game::instance().unload();
	}
	Game::instance().close();

	return 0;
}