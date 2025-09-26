#pragma once

class MenuScreen
{
	friend class Game;
protected:
	MenuScreen(Game* game);
	void Update();

	void DrawButtons();
	void DrawCustomRoundSettings();

private:
	Game* game;


	int iFieldWidth = 25;
	int iFieldHeight = 15;
	int iFieldMines = 50;
};