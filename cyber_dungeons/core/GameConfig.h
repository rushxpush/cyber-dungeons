#pragma once

#include <raylib.h>


struct GameConfig
{
	int screenWidth;
	int screenHeight;
	const char* title;

	GameConfig(int screenWidth, int screenHeight, const char* title) : 
	screenWidth(screenWidth),
	screenHeight(screenHeight),
	title(title)
	{
		InitWindow(screenWidth, screenHeight, title);
		SetTargetFPS(60);
	}
};