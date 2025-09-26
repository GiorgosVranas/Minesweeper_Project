#pragma once
#include "raylib.h"

namespace SpriteMapping
{

	// Status bar slices
	Rectangle g_pRecStatusFaces[4] = {
	   {0.0f, 0.0f, 96.0f, 96.0f},
	   {96.0f, 0.0f, 96.0f, 96.0f},
	   {0.0f, 96.0f, 96.0f, 96.0f},
	   {96.0f, 96.0f, 96.0f, 96.0f}
	};

	Rectangle g_pRecStatusNumbers[10] = {
		{224.0f, 0.0f, 32.0f, 56.0f},
		{256.0f, 0.0f, 32.0f, 56.0f},
		{288.0f, 0.0f, 32.0f, 56.0f},
		{192.0f, 56.0f, 32.0f, 56.0f},
		{224.0f, 56.0f, 32.0f, 56.0f},
		{256.0f, 56.0f, 32.0f, 56.0f},
		{288.0f, 56.0f, 32.0f, 56.0f},
		{192.0f, 112.0f, 32.0f, 56.0f},
		{224.0f, 112.0f, 32.0f, 56.0f},
		{256.0f, 112.0f, 32.0f, 56.0f}
	};

	Rectangle g_pRecStatusNumber_Blank = { 192.0f, 0.0f, 32.0f, 56.0f };
	Rectangle g_pRecStatusNumber_Colon = { 288.0f, 112.0f, 32.0f, 56.0f };
	Rectangle g_pRecStatusNumber_Mine = { 320.0f, 0.0f, 32.0f, 56.0f };
}

extern void DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint);
