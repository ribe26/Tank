// Tank.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

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

