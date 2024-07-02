#include <iostream>
#include "Game.h"

int main(int argc, char** argv)
{
    std::cout << "Hello World!\n";
    Game game;
	bool success = game.Initialize();
	if (success)
	{
		std::cout << "did it";
	}
	game.mainLoop();

    return 0;
}

