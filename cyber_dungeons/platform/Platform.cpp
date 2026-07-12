#include "Platform.h"

Platform::Platform(float x, float y, float width, float height) : 
    rect{x, y, width, height} {}

void Platform::render() const
{
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, BLUE);
}
