#pragma once
#include "ResourceManager.h"

struct ButtonColorSet
{
	Color ColorA;
	Color ColorB;
	Color ColorC;
	Color ColorD;
	Color Background;
};


struct NumberButtonColorSet
{
	Color ColorA;
	Color ColorB;
	Color Background;
	Color Arrow;
};

class GUI
{
public:
	GUI(ResourceManager* ResourceMgr);
	bool Button(Rectangle bounds, const char* text);
	void NumberEntry(int x, int y, int* value, int min, int max);
private:
	void DrawButton(ButtonColorSet colors, Rectangle bounds, const char* text);
	void DrawBase(Rectangle bounds);
	void DrawTopButton(Rectangle bounds, int* value, int max);
	void DrawBottomButton(Rectangle bounds, int* value, int min);

private:
	ResourceManager* ResourceMgr = nullptr;

	const ButtonColorSet ButtonNormalColorSet = {
		{ 69,  69,  69, 255 },
		{154, 154, 154, 255 },
		{186, 186, 186, 255 },
		{223, 223, 223, 255 },
		{255, 255, 255, 255 } 
	};

	const ButtonColorSet ButtonHoverColorSet = {
		{ 69,  69,  69, 255 },
		{117, 117, 117, 255 },
		{154, 154, 154, 255 },
		{186, 186, 186, 255 },
		{223, 223, 223, 255 } 
	};

	const NumberButtonColorSet NumberButtonNormalColorSet = {
		{154, 154, 154, 255 },
		{223, 223, 223, 255 },
		{255, 255, 255, 255 },
		{ 69,  69,  69, 255 } 
	};

	const NumberButtonColorSet NumberButtonShadedColorSet = {
		{154, 154, 154, 255 }, 
		{223, 223, 223, 255 }, 
		{223, 223, 223, 255 }, 
		{154, 154, 154, 255 } 
	};

	const NumberButtonColorSet NumberButtonHoverColorSet = {
		{154, 154, 154, 255 },
		{186, 186, 186, 255 },
		{223, 223, 223, 255 },
		{ 69,  69,  69, 255 }
	};

};