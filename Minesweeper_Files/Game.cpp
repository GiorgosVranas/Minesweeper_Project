#include "Game.h"
#include "MenuScreen.h"
#include "Minefield.h"
#include "raylib.h"

Game::Game()
{
	ResourceMgr = new ResourceManager();
	MGUI = new GUI(ResourceMgr);
	menuScreen = new MenuScreen(this);
	minefield = new Minefield(this);
}

Game::~Game()
{
	delete MGUI;
	delete ResourceMgr;
	delete menuScreen;
	delete minefield;
}

void Game::Init()
{
	// Arxikopoihsh window
	InitWindow(800, 600, "Mines!");
	SetTargetFPS(60);

	InitAudioDevice();

	ResourceMgr->Init();

	// orismos window icon
	SetWindowIcon(ResourceMgr->GetWindowIcon());
}

void Game::Update()
{
	// Sxedio
	BeginDrawing();
	ClearBackground(WHITE);

	switch (GameState) {
	case GAMESTATE_MENU:
		menuScreen->Update();
		break;
	case GAMESTATE_MINEFIELD:
		minefield->Update();
		break;
	}

	EndDrawing();
}

void Game::Shutdown()
{

	ResourceMgr->Shutdown();

	//Kleisimo Audio kai Window
	CloseAudioDevice();
	CloseWindow();
}

bool Game::ShouldUpdate()
{
	return !WindowShouldClose() && !bShouldQuit;
}

void Game::WinGame()
{
	bGameWon = true;
	PlaySound(ResourceMgr->GetSndWin());
}

void Game::NewGame()
{
	bGameOver = false;
	bGameWon = false;
}

void Game::StartGame(int width, int height, int mines)
{
	minefield->Generate(width, height, mines);
	minefield->PrepareStart();
	GameState = GAMESTATE_MINEFIELD;
}

void Game::Reset()
{
	bGameWon = false;
	bGameOver = false;
	minefield->Reset();
}
