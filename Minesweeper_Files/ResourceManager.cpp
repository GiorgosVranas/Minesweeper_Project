#include "ResourceManager.h"

void ResourceManager::Init()
{
	WindowIcon = LoadImage("icon32.png");

	TexUIArrowUp = LoadTexture("./resources/textures/ui_arrow_up.png");
	TexUIArrowDown = LoadTexture("./resources/textures/ui_arrow_down.png");

	TexMenuBG = LoadTexture("./resources/textures/splash.png");
	TexFieldCells = LoadTexture("./resources/textures/fieldcells.png");
	TexTopCells = LoadTexture("./resources/textures/topcells.png");
	TexStatusBar = LoadTexture("./resources/textures/statusbar.png");

	SndExplode = LoadSound("./resources/sounds/explode.ogg");
	SndWin = LoadSound("./resources/sounds/win.ogg");
}


void ResourceManager::Shutdown()
{
	UnloadImage(WindowIcon);

	UnloadTexture(TexUIArrowUp);
	UnloadTexture(TexUIArrowDown);

	UnloadTexture(TexMenuBG);
	UnloadTexture(TexFieldCells);
	UnloadTexture(TexTopCells);
	UnloadTexture(TexStatusBar);

	UnloadSound(SndExplode);
	UnloadSound(SndWin);
}