#pragma once

#include <raylib.h>

class Platform
{
public:
    Rectangle rect;

    Texture2D texture;

    Platform(float x, float y, float width, float height);

    void render() const;
    void destroy() const;
};
