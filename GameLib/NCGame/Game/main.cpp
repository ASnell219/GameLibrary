#include "game.h"
#include "engine.h"


int main(int argc, char* argv[])
{
	Engine engine;
	Game game(&engine);

	game.Initialize();
	while (game.Run()) game.Update();
	game.Shutdown();

  	return 0;
}