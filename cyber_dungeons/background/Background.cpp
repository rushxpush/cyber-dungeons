#include <Background.h>
#include <raylib.h>

Background::Background(int screenWidth, int screenHeight, const char* imagePath) : 
	screenWidth(screenWidth),
	screenHeight(screenHeight),
	imagePath(imagePath)
	{
		Image backgroundImage = LoadImage(imagePath);
		texture = LoadTextureFromImage(backgroundImage);
		UnloadImage(backgroundImage);
	}

void Background::render() const
{
	DrawTexture(texture, 0, 0, WHITE);
}

void Background::destroy() {
	UnloadTexture(texture);
}
