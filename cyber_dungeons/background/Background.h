#pragma once

#include <raylib.h>
#include <cmath>

class Background
{
private:
	int screenWidth;
	int screenHeight;

	Texture2D texture;

public:
	Background(int screenWidth, int screenHeight);

	// core
	void render() const;
	void destroy() const;
};