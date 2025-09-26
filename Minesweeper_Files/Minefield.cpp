#include "Minefield.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "SpriteMapping.h"
#include "Game.h"
#include <raymath.h>


Minefield::Minefield(Game* game)
{
	this->game = game;
}

Minefield::~Minefield()
{
	delete[] this->pField;
	delete[] this->pTop;
}

void Minefield::Update()
{
	DrawPanel();
	DrawStatusBar();
	DrawCounters();
	DrawMenuOptions();
	DrawMineField();

	ProcessWin();
	ProcessGame();
}

void Minefield::DrawPanel()
{
	DrawRectangle(0, 0, GetScreenWidth(), 120, Color{ 255, 255, 255, 255 });  
	DrawRectangleLines(0, 0, GetScreenWidth(), 120, Color{ 85, 85, 85, 255 });   
	DrawRectangleLines(1, 1, GetScreenWidth() - 2, 118, Color{ 170, 170, 170, 255 });   

	DrawRectangle(0, 120, 800, 480, Color{ 170, 170, 170, 255 });   
	DrawRectangleLines(0, 120, 800, 480, Color{ 117, 117, 117, 255 });   
	DrawRectangleLines(1, 121, 798, 478, Color{ 138, 138, 138, 255 });   
}

void Minefield::DrawStatusBar()
{
	// status bar
	DrawTextureRec( 
		game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusFaces[StatusFace],
		{ GetScreenWidth() / 2 - 126.0f, 12.0f },
		WHITE
	);
    //counter
	DrawTextureRec( 
		game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusNumber_Mine,
		{ 32.0f, 36.0f },
		WHITE
	);

	DrawTextureTiled( 
		game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusNumber_Blank,
		{ 64.0f, 36.0f, 96.0f, 56.0f },
		{ 0.0f, 0.0f },
		0.0f, 1.0f, WHITE
	);
}

void Minefield::DrawCounters()
{
	//arithmoi
	std::ostringstream oss;
	oss << std::setw(4) << (int)Clamp(iFieldMines - iPlacedFlags, 0, 9999);
	std::string txt_timer = oss.str();
	char* txt = txt_timer.data();


	DrawTextureRec(game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusNumbers[txt[0] - '0'], { 64.0f, 36.0f }, WHITE);
	DrawTextureRec(game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusNumbers[txt[1] - '0'], { 96.0f, 36.0f }, WHITE);
	DrawTextureRec(game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusNumbers[txt[2] - '0'], { 128.0f, 36.0f }, WHITE);

	//Mhdenika
	DrawTextureTiled( 
		game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusNumber_Blank,
		Rectangle{
		GetScreenWidth() - 160.0f, 36.0f, 128.0f, 56.0f
		},
		{ 0.0f, 0.0f },
		0.0f, 1.0f, WHITE
	);

	
	if (bDoTimer) 
		iRoundTimer = GetTime() - iRoundStart;

	oss.clear();
	oss << std::setw(4) << (int)Clamp(iRoundTimer, 0, 9999);
	txt_timer = oss.str();
	txt = txt_timer.data();

	DrawTextureRec(game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusNumbers[txt_timer[0] - '0'], { GetScreenWidth() - 160.0f, 36.0f }, WHITE);
	DrawTextureRec(game->GetResourceMgr()->GetTexStatusBar(), 
		SpriteMapping::g_pRecStatusNumbers[txt_timer[1] - '0'], { GetScreenWidth() - 128.0f, 36.0f }, WHITE);
	DrawTextureRec(game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusNumbers[txt_timer[2] - '0'], { GetScreenWidth() - 96.0f, 36.0f }, WHITE);
	DrawTextureRec(game->GetResourceMgr()->GetTexStatusBar(),
		SpriteMapping::g_pRecStatusNumbers[txt_timer[3] - '0'], { GetScreenWidth() - 64.0f, 36.0f }, WHITE);
}

void Minefield::DrawMenuOptions()
{
	
	if (game->MGUI->Button({ GetScreenWidth() / 2 - 18.0f, 12.0f, 144.0f, 32.0f }, "NEW GAME")) {
		NewGame();
	}

	if (game->MGUI->Button({ GetScreenWidth() / 2 - 18.0f, 52.0f, 144.0f, 32.0f }, "MENU")) {
		game->ToMainMenu();
	}
}

void Minefield::DrawMineField()
{
	
	for (int x = 0; x < iFieldWidth; x++) {
		for (int y = 0; y < iFieldHeight; y++) {
			int fieldcell_value = pField[(y * iFieldWidth) + x];
			int topcell_value = pTop[(y * iFieldWidth) + x];

			
			DrawTexturePro(
				game->GetResourceMgr()->GetTexFieldCells(),
				Rectangle{
				fieldcell_value * 32.0f, 0.0f, 
					32.0f, 32.0f
				},
				Rectangle{
				x * 32.0f, 120.0f + y * 32.0f,
					32.0f, 32.0f
				},
				{ 0.0f, 0.0f },
				0.0f,
				WHITE
			);

			
			DrawTexturePro(
				game->GetResourceMgr()->GetTexTopCells(),
				{
					topcell_value * 32.0f, 0.0f, 
					32.0f, 32.0f
				},

				{
					x * 32.0f, 120.0f + y * 32.0f,
					32.0f, 32.0f
				},
				{ 0.0f, 0.0f },
				0.0f,
				WHITE
			);
		}
	}


}

void Minefield::ProcessWin()
{
	// Count stats
	int revealed_cells = 0;
	if (!game->IsGameOver()) {
		iPlacedFlags = 0;

		for (int i = 0; i < iFieldWidth * iFieldHeight; i++) {
			if (pTop[i] == TOPCELL_NONE) revealed_cells++;
			if (pTop[i] == TOPCELL_FLAG) iPlacedFlags++;
		}
	}

	// Elegxos an uparxei nikh
	if ((revealed_cells == (iFieldWidth * iFieldHeight) - iFieldMines) && (!game->IsGameWon())) {
		WinGame();
	}
}

void Minefield::ProcessGame()
{
	
	int selection_x = floor((float)GetMouseX() / 32.0f);
	int selection_y = floor(((float)GetMouseY() - 120.0f) / 32.0f);
	int selection_pos = (selection_y * iFieldWidth) + selection_x;

	if (
		(GetMouseY() > 120) &&
		(GetMouseY() < iFieldHeight * 32 + 120) &&
		(GetMouseX() < iFieldWidth * 32.0f) &&
		(!(game->IsGameWon() || game->IsGameOver()))
		) {
		
		DrawRectangleLines(
			selection_x * 32.0f,
			selection_y * 32.0f + 120.0f,
			32.0f, 32.0f,
			{ 0, 113, 0, 255 }
		);

		DrawRectangleLines(
			selection_x * 32.0f + 1.0f,
			selection_y * 32.0f + 121.0f,
			30.0f, 30.0f,
			{ 0, 170, 0, 255 }
		);

		// Click
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			if (bDoTimer) StatusFace = STATUSFACE_SURPRISED;
		}
		else {
			StatusFace = STATUSFACE_HAPPY;
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {   //vgale vomva
			if (pTop[selection_pos] == TOPCELL_FLAG) { 
				pTop[selection_pos] = TOPCELL_BLANK;
			}
			else if (pTop[selection_pos] == TOPCELL_BLANK) { 
				
				while ((pField[selection_pos] == FIELDCELL_MINE) && iClickedCells == 0) {
					Generate(iFieldWidth, iFieldHeight, iFieldMines);
				}

				if (!bDoTimer) iRoundStart = GetTime();
				bDoTimer = true;
				iClickedCells++;

				
				if (pField[selection_pos] == FIELDCELL_MINE) { //otan patisei se bomba xanei
					LoseGame();

				
					for (int i = 0; i < iFieldWidth * iFieldHeight; i++) {
					
						if (pField[i] == FIELDCELL_MINE) {
							pTop[i] = TOPCELL_NONE;
						}

						
						if (pTop[i] == TOPCELL_FLAG) {
							pTop[i] = (pField[i] == FIELDCELL_MINE) ?  
								TOPCELL_NONE :      
								TOPCELL_WRONGFLAG;  
						}
					}

					pTop[selection_pos] = TOPCELL_CURMINE; // Markare auto poy patise

					PlaySound(game->GetResourceMgr()->GetSndExplode()); 
				}
				else if (pField[selection_pos] == FIELDCELL_EMPTY) { // otan den exei arithmo
					RevealEmptyCells(selection_x, selection_y);
				}
				else { //otan exei arithmo
					pTop[selection_pos] = TOPCELL_NONE; 
				}
			}
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			bDoTimer = true;

			if (pTop[selection_pos] == TOPCELL_BLANK) {
				pTop[selection_pos] = TOPCELL_FLAG;
			}
			else if (pTop[selection_pos] == TOPCELL_FLAG) {
				pTop[selection_pos] = TOPCELL_BLANK;
			}
		}
	}

}

void Minefield::NewGame()
{
	Generate(iFieldWidth, iFieldHeight, iFieldMines);

	iRoundStart = GetTime();
	iRoundTimer = 0;
	bDoTimer = false;

	StatusFace = STATUSFACE_HAPPY;

	game->NewGame();
}

void Minefield::WinGame()
{
	bDoTimer = false;
	StatusFace = STATUSFACE_COOL;

	game->WinGame();
}

void Minefield::LoseGame()
{
	bDoTimer = false;
	StatusFace = STATUSFACE_DEAD;

	game->SetGameOver(true);
}

void Minefield::Reset()
{
	bDoTimer = false;
	iRoundTimer = 0;
	iRoundStart = 0;
	StatusFace = STATUSFACE_HAPPY;
}

void Minefield::PrepareStart()
{
	iRoundStart = GetTime();
	iClickedCells = 0;
}

void Minefield::Generate(int width, int height, int mines)
{
	SetWindowSize(fmax(width * 32, 800), fmax(height * 32 + 120, 600));

	
	iFieldWidth = width;
	iFieldHeight = height;
	iFieldMines = mines;

	game->bGameOver = false;
	iClickedCells = 0;


	if (pField != nullptr)
		delete[] pField;

	if (pTop != nullptr)
		delete pTop;

	size_t arrSizeFull = iFieldWidth * iFieldHeight;


	pField = new eFieldCell[arrSizeFull];
	pTop = new eTopCell[arrSizeFull];


	for (int i = 0; i < arrSizeFull; i++) {
		pField[i] = FIELDCELL_EMPTY;
		pTop[i] = TOPCELL_BLANK;
	}


	int placed_mines = 0;

	while (placed_mines != mines) { 
		int rx = GetRandomValue(0, iFieldWidth - 1);
		int ry = GetRandomValue(0, iFieldHeight - 1);
		int i = (ry * iFieldWidth) + rx;

		if (pField[i] != FIELDCELL_MINE) { 
			pField[i] = FIELDCELL_MINE;
			placed_mines++;
		}
	}

	
	for (int x = 0; x < iFieldWidth; x++) {
		for (int y = 0; y < iFieldHeight; y++) {
			int idx = (y * iFieldWidth) + x;

			pField[idx] = (eFieldCell)GetCellNumber(x, y);
		}
	}
}

int Minefield::GetCellNumber(int x, int y)
{
	if ((x < 0) || (y < 0)) return -1;
	if ((x >= iFieldWidth) || (y >= iFieldHeight)) return -1;


	int mines = 0;
	int initpos = (y * iFieldWidth) + x;

	if (pField[initpos] == FIELDCELL_MINE) return 9;

	
	for (int xoff = -1; xoff < 2; xoff++) {
		for (int yoff = -1; yoff < 2; yoff++) {
			int pos = ((y + yoff) * iFieldWidth) + (x + xoff); 

			if ( 
				((x + xoff) < 0) || ((y + yoff) < 0) ||
				((x + xoff) >= iFieldWidth) || ((y + yoff) >= iFieldHeight)
				) {
				continue;
			}
			else {
				if (pField[pos] == FIELDCELL_MINE) mines++;
			}
		}
	}

	return mines;

}

void Minefield::RevealEmptyCells(int x, int y)
{
	int idx = (y * iFieldWidth) + x;

	if ((x < 0) || (y < 0)) return;
	if ((x >= iFieldWidth) || (y >= iFieldWidth)) return;

	int cell_number = GetCellNumber(x, y);

	if ((cell_number == 0) && (pTop[idx] != TOPCELL_NONE)) {
		pTop[idx] = TOPCELL_NONE;

		RevealEmptyCells(x, y - 1);
		RevealEmptyCells(x, y + 1);
		RevealEmptyCells(x - 1, y);
		RevealEmptyCells(x + 1, y);
	}
	else if (GetCellNumber(x, y) != -1) {
		pTop[idx] = TOPCELL_NONE;
	}
}
