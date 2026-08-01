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
		//SetConfigFlags(FLAG_FULLSCREEN_MODE);
		InitWindow(screenWidth, screenHeight, title);
		SetTargetFPS(60);
	}
};