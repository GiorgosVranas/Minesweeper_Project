#pragma once
#include "ResourceManager.h"
#include "GUI.hpp"

enum eGameState
{
    GAMESTATE_MENU,
    GAMESTATE_MINEFIELD
};

class Game
{
    friend class MenuScreen;
    friend class Minefield;
public:
	Game();
	~Game();
public:
	void Init();
    void Update();
    void Shutdown();

    bool ShouldUpdate();

    ResourceManager* GetResourceMgr() {
        return ResourceMgr;
    }

    GUI* GetGUI() {
        return MGUI;
    }
     
    bool IsGameOver() {
        return bGameOver;
    }

    void SetGameOver(bool val) {
        bGameOver = val;
    }

    bool IsGameWon() {
        return bGameWon;
    }

    void SetGameWon(bool val) {
        bGameWon = val;
    }

    void ToMainMenu() {
        GameState = GAMESTATE_MENU;
    }

    void QuitGame() {
        bShouldQuit = true;
    }

    void WinGame();
    void NewGame();
    void StartGame(int width, int height, int mines);
    void Reset();

private:
	ResourceManager* ResourceMgr = nullptr;
    GUI* MGUI = nullptr;

    Minefield* minefield;
    MenuScreen* menuScreen;

    eGameState GameState = GAMESTATE_MENU;

    bool bGameOver = false;
    bool bGameWon = false;
    bool bShouldQuit = false;
};