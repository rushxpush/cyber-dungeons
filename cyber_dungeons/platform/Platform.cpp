#include "Platform.h"
#include <cmath>

Platform::Platform(float x, float y, float width, float height) : 
    rect{x, y, width, height} 
    {
        Image playerImage = LoadImage("resources/images/platform.png");
        texture = LoadTextureFromImage(playerImage);
        UnloadImage(playerImage);
    }

void Platform::render() const
{
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, BLUE);

    int platformBlocksQuantityHorizontal = rect.width / 20;
    int platformBlocksQuantityVertical = rect.height / 20;

    for (int i = 0; i < platformBlocksQuantityHorizontal; i++)
    {
        for (int j = 0; j < platformBlocksQuantityVertical; j++)
        {
            DrawTexture(texture, std::floor(rect.x + i * 20), std::floor(rect.y + j * 20), WHITE);
        }
    }
}

void Platform::destroy() const
{
    UnloadTexture(texture);
}
