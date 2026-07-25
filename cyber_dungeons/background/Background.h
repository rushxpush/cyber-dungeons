#pragma once

#include <raylib.h>
#include <cmath>

class Background
{
private:
	int screenWidth;
	int screenHeight;
	const char* imagePath;

	Texture2D texture;
public:
	Background(int screenWidth, int screenHeight, const char* imagePath);

	// core
	void render() const;
	void destroy() const;
};