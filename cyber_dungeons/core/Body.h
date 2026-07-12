#pragma once

#include "raylib.h"

struct Body {
    Rectangle rect;
    Rectangle previousRect;
    float vertical_speed;

    Body(float x, float y, float width, float height, float vertical_speed) : 
        rect{ x, y, width, height }, 
        previousRect{ x, y, width, height }, 
        vertical_speed(vertical_speed)
    {}

    void setPosition(float x, float y)
    {
        rect.x = x;
        rect.y = y;
    }

    void setVerticalSpeed(float speed)
    {
        vertical_speed = speed;
    }

    float getVerticalSpeed() const
    {
        return vertical_speed;
    }

    void move(float dx, float dy)
    {
        rect.x += dx;
        rect.y += dy;
    }

    Rectangle getRect() const
    {
        return rect;
    }

    Rectangle getPreviousRect() const
    {
        return previousRect;
    }

    void storePreviousRect()
    {
        previousRect = rect;
    }
};
