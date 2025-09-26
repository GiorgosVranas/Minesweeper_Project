#pragma once
#include <raylib.h>

// Cell types
enum eFieldCell
{
	FIELDCELL_EMPTY,
	FIELDCELL_ONE,
	FIELDCELL_TWO,
	FIELDCELL_THREE,
	FIELDCELL_FOUR,
	FIELDCELL_FIVE,
	FIELDCELL_SIX,
	FIELDCELL_SEVEN,
	FIELDCELL_EIGHT,
	FIELDCELL_MINE,
	_FIELDCELL_COUNT
};

enum eTopCell
{
	TOPCELL_NONE,
	TOPCELL_BLANK,
	TOPCELL_FLAG,
	TOPCELL_CURMINE,
	TOPCELL_WRONGFLAG
};


enum eStatusFace
{
	STATUSFACE_HAPPY,
	STATUSFACE_SURPRISED,
	STATUSFACE_COOL,
	STATUSFACE_DEAD
};


class Minefield
{
	friend class Game;
protected:

	Minefield(Game* game);
	~Minefield();

	void Update();
private:
	void DrawPanel();
	void DrawStatusBar();
	void DrawCounters();
	void DrawMenuOptions();
	void DrawMineField();

	void ProcessWin();
	void ProcessGame();

	void NewGame();
	void WinGame();
	void LoseGame();

	void Reset();
	void PrepareStart();

protected:
	void Generate(int width, int height, int mines);
private:
	int GetCellNumber(int x, int y);
	void RevealEmptyCells(int x, int y);


private:


	Game* game = nullptr;

	eFieldCell* pField = 0;
	eTopCell* pTop = 0;

	int iFieldWidth = 25;
	int iFieldHeight = 15;
	int iFieldMines = 50;
	int iClickedCells = 0;
	int iPlacedFlags = 0;
	int iRoundStart = 0;
	int iRoundTimer = 0;

	bool bDoTimer = false;

	eStatusFace StatusFace = STATUSFACE_HAPPY;
};