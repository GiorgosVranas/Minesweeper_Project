#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Game.h"

//#pragma comment(lib, "raylib.lib")
#pragma comment(lib, "winmm.lib")

int main(int argc, char** argv) {
	Game* game = new Game();

	game->Init();
	while (game->ShouldUpdate())
	{
		game->Update();
	}
	game->Shutdown();

	delete game;
	return true;
}