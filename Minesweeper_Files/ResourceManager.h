#pragma once

#include <raylib.h>

class ResourceManager
{
	friend class Game;
protected:
	void Init();
	void Shutdown();

public:
	Image& GetWindowIcon() { return WindowIcon; }

	Texture& GetTexMenuBG() { return TexMenuBG; }
	Texture& GetTexFieldCells() { return TexFieldCells; }
	Texture& GetTexTopCells() { return TexTopCells; }
	Texture& GetTexStatusBar() { return TexStatusBar; }

	Texture& GetTexUIArrowUp() { return TexUIArrowUp; }
	Texture& GetTexUIArrowDown() { return TexUIArrowDown; }

	Sound& GetSndExplode() { return SndExplode; }
	Sound& GetSndWin() { return SndWin; }

private:
	Image WindowIcon = { 0 };

	Texture TexMenuBG = { 0 };
	Texture TexFieldCells = { 0 };
	Texture TexTopCells = { 0 };
	Texture TexStatusBar = { 0 };

	Texture TexUIArrowUp = { 0 };
	Texture TexUIArrowDown = { 0 };

	Sound SndExplode = { 0 };
	Sound SndWin = { 0 };
};