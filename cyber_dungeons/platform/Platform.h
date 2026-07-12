#pragma once

#include <raylib.h>

class Platform
{
public:
    Rectangle rect;

    Platform(float x, float y, float width, float height);

    void render() const;
};
