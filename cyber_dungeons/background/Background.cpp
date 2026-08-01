#include <Background.h>
#include <raylib.h>
#include "GameCamera.h"
#include <iostream>

Background::Background(int screenWidth, int screenHeight, const char* imagePath, ZPosition zPosition) : 
	screenWidth(screenWidth),
	screenHeight(screenHeight),
	imagePath(imagePath),
	zPosition(zPosition)
	{
		std::cout << "CTOR " << imagePath << std::endl;
		Image backgroundImage = LoadImage(imagePath);
		texture = LoadTextureFromImage(backgroundImage);
		UnloadImage(backgroundImage);
	}

Background::Background(Background&& other) noexcept
{
	texture = other.texture;
	other.texture = {};
	imagePath = other.imagePath;
	screenWidth = other.screenWidth;
	screenHeight = other.screenHeight;
	zPosition = other.zPosition;
}

Background& Background::operator=(Background&& other) noexcept
{
	if (this != &other)
	{
		if (texture.id != 0)
		{
			UnloadTexture(texture);
		}
		texture = other.texture;
		other.texture = {};
	}
	return *this;
}

Background::~Background()
{
	std::cout << "DTOR " << imagePath << std::endl;
	if (texture.id != 0)
	{
		std::cout << "texture.id: " << texture.id << std::endl;
		UnloadTexture(texture);
	}
}

void Background::render() const
{
	DrawTexture(texture, 0, 0, WHITE);
}

Camera2D Background::getCamera() const
{
	return camera.getCamera();
}
