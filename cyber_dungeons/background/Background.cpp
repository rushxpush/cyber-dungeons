#include <Background.h>
#include <raylib.h>

Background::Background(int screenWidth, int screenHeight) : 
	screenWidth(screenWidth),
	screenHeight(screenHeight) 
	{
		Image backgroundImage = LoadImage("resources/images/background.png");
		texture = LoadTextureFromImage(backgroundImage);
		UnloadImage(backgroundImage);
	}

void Background::render() const
{
	DrawTexture(texture, 0, 0, WHITE);
}

void Background::destroy() const {
	UnloadTexture(texture);
}
