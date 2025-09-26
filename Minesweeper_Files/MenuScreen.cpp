#include "MenuScreen.h"
#include "Game.h"
#include <raylib.h>
#include <raymath.h>


MenuScreen::MenuScreen(Game* game)
{
	this->game = game;
}


void MenuScreen::Update()
{
	//orismos window size
	SetWindowSize(800, 600);

	game->Reset();


	//background
	DrawTexture(game->GetResourceMgr()->GetTexMenuBG(), 0, 0, WHITE);

	DrawButtons();
	DrawCustomRoundSettings();

	if (game->GetGUI()->Button(Rectangle{ 328.0f, 284.0f + 256.0f, 144.0f, 32.0f }, "QUIT")) {
		game->QuitGame();
	}
}

void MenuScreen::DrawButtons()
{
	//buttons
	DrawText("10x10 | 10 Mines", 280, 284 + 8, 20, Color{ 0x00, 0x00, 0x00, 0x7f });
	if (game->GetGUI()->Button({ 128.0f, 284.0f, 144.0f, 32.0f }, "BEGINNER")) {
		game->StartGame(10, 10, 10);
	}

	DrawText("25x15 | 50 Mines", 280, 284 + 48 + 8, 20, Color{ 0x00, 0x00, 0x00, 0x7f });
	if (game->GetGUI()->Button({ 128.0f, 284.0f + 48.0f, 144.0f, 32.0f }, "DIFFICULT")) {
		game->StartGame(25, 15, 50);
	}

	DrawText("30x15 | 99 Mines", 280, 284 + 96 + 8, 20, Color{ 0x00, 0x00, 0x00, 0x7f });
	if (game->GetGUI()->Button({ 128.0f, 284.0f + 96.0f, 144.0f, 32.0f }, "EXPERT")) {
		game->StartGame(30, 15, 99);
	}

}

void MenuScreen::DrawCustomRoundSettings()
{
	int maxmines = (iFieldWidth * iFieldHeight) - 1;

	
	if (game->GetGUI()->Button({ 464.0f, 380.0f, 208.0f, 32.0f }, "CUSTOM")) {
		game->StartGame(iFieldWidth, iFieldHeight, iFieldMines);
	}

	DrawText("W", 512 - 20, 290, 20, Color{ 0, 0, 0, 0 });
	game->GetGUI()->NumberEntry(512, 284, &iFieldWidth, 5, 50);

	DrawText("H", 608 - 20, 290, 20, Color{ 0, 0, 0, 127 });
	game->GetGUI()->NumberEntry(608, 284, &iFieldHeight, 5, 25);

	DrawText("Mines", 608 - 60, 338, 20, Color{ 0, 0, 0, 127 });
	game->GetGUI()->NumberEntry(608, 332, &iFieldMines, 1, Clamp(maxmines, 1, 199));
}
