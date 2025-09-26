#include "GUI.hpp"
#include <string>
#include <raymath.h>

GUI::GUI(ResourceManager* ResourceMgr)
{
	this->ResourceMgr = ResourceMgr;
}

bool GUI::Button(Rectangle bounds, const char* text)
{
	if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
		bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
		DrawButton(ButtonHoverColorSet, bounds, text);
		return clicked;
	}
	else {
		DrawButton(ButtonNormalColorSet, bounds, text);
	}

	return false;
}

void GUI::NumberEntry(int x, int y, int* value, int min, int max)
{
	if (value == 0) return;

	// Oria
	Rectangle bounds = {
		(float)x, (float)y,
		64.0f, 32.0f
	};

	Rectangle topbtn_bounds = {
		x + 41, (float)y + 1,
		22.0f, 15.0f
	};

	Rectangle bottombtn_bounds = {
		x + 41, (float)y + 16,
		22.0f, 15.0f
	};

	// Sxediasmos vashs
	DrawBase(bounds);


	DrawLine(x + 40, y + 1, x + 40, y + 30, { 154, 154, 154, 255 });
	DrawLine(x + 41, y, x + 41, y + 32, { 69, 69, 69, 255 });
	DrawLine(x + 42, y + 1, x + 42, y + 30, { 154, 154, 154, 255 });


	DrawTopButton(topbtn_bounds, value, max);
	DrawBottomButton(bottombtn_bounds, value, min);

	// Scrolling
	if (CheckCollisionPointRec(GetMousePosition(), { (float)x, (float)y, 64.0f, 32.0f })) {
		*value += GetMouseWheelMove();
	}

	
	*value = Clamp(*value, min, max);

	std::string txt = std::to_string(*value);
	DrawText(txt.c_str(), x + 10, y + 7, 20, BLACK);
}

void GUI::DrawButton(ButtonColorSet colors, Rectangle bounds, const char* text)
{
	
	DrawRectangleRec({ bounds.x, bounds.y, bounds.width, bounds.height }, colors.ColorA);
	DrawRectangleRec({ bounds.x + 1, bounds.y + 1, bounds.width - 2, bounds.height - 2 }, colors.ColorB);
	DrawRectangleRec({ bounds.x + 2, bounds.y + 2, bounds.width - 4, bounds.height - 4 }, colors.ColorC);
	DrawRectangleRec({ bounds.x + 3, bounds.y + 3, bounds.width - 6, bounds.height - 6 }, colors.ColorD);
	DrawRectangleRec({ bounds.x + 4, bounds.y + 4, bounds.width - 8, bounds.height - 8 }, colors.Background);

	// text
	Vector2 textbounds = MeasureTextEx(GetFontDefault(), text, 20, 2.0f);

	DrawTextEx(GetFontDefault(), text,
	 {
		  bounds.x + (bounds.width - textbounds.x) / 2.0f,
		  bounds.y + (bounds.height - textbounds.y) / 2.0f,
	 },20, 2.0f, BLACK);
}

void GUI::DrawBase(Rectangle bounds)
{
	
	DrawRectangleRec(
		{ bounds.x, bounds.y, bounds.width, bounds.height },
		{ 0x45, 0x45, 0x45, 0xff }
	);

	DrawRectangleRec(
		{ bounds.x + 1, bounds.y + 1, bounds.width - 2, bounds.height - 2 },
		{ 0x9a, 0x9a, 0x9a, 0xff }
	);

	DrawRectangleRec(
		{ bounds.x + 2, bounds.y + 2, bounds.width - 4, bounds.height - 4 },
		{ 0xdf, 0xdf, 0xdf, 0xff }
	);
}

void GUI::DrawTopButton(Rectangle bounds, int* value, int max)
{
	NumberButtonColorSet buttonColor = NumberButtonNormalColorSet;

	if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) *value += 1;

		buttonColor = NumberButtonHoverColorSet;
	}
	else {
		buttonColor = NumberButtonNormalColorSet;
	}
	buttonColor.Arrow = NumberButtonNormalColorSet.Arrow;
	if (*value >= max) {
		buttonColor = NumberButtonShadedColorSet;
	}

	DrawRectangleRec(bounds, buttonColor.ColorA);
	DrawRectangleRec({ bounds.x + 1, bounds.y + 1, bounds.width - 2, bounds.height - 2 }, buttonColor.ColorB);
	DrawRectangleRec({ bounds.x + 2, bounds.y + 2, bounds.width - 4, bounds.height - 4 }, buttonColor.Background);
   
	DrawTexture(ResourceMgr->GetTexUIArrowUp(), bounds.x, bounds.y, buttonColor.Arrow);

}

void GUI::DrawBottomButton(Rectangle bounds, int* value, int min)
{
	NumberButtonColorSet buttonColor = NumberButtonNormalColorSet;

	if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) *value -= 1;

		buttonColor = NumberButtonHoverColorSet;
	}
	else {
		buttonColor = NumberButtonNormalColorSet;
	}
	buttonColor.Arrow = NumberButtonNormalColorSet.Arrow;
	if (*value <= min) {
		buttonColor = NumberButtonShadedColorSet;
	}

	DrawRectangleRec(bounds, buttonColor.ColorA);
	DrawRectangleRec({ bounds.x + 1, bounds.y + 1, bounds.width - 2, bounds.height - 2 }, buttonColor.ColorB);
	DrawRectangleRec({ bounds.x + 2, bounds.y + 2, bounds.width - 4, bounds.height - 4 }, buttonColor.Background);

	DrawTexture(ResourceMgr->GetTexUIArrowDown(), bounds.x, bounds.y, buttonColor.Arrow);
}
