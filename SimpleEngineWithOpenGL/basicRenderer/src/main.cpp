#include"game.h"

int main(int argc, char** argv)
{
	// instanciate the game singleton
	bool isGameInit = Game::instance().initialize();
	if (isGameInit)
	{
		// Load all the textures, meshes, shader...
		Game::instance().load();
		// Loop the game
		Game::instance().loop();
		// Unload all the textures
		Game::instance().unload();
	}
	//CLose the game singleton
	Game::instance().close();

	return 0;
}