#pragma once

#include "raylib.h"
#include "Direction.h"

struct Body {
    Rectangle rect;
    Rectangle previousRect;
    float vertical_speed;
    Direction direction;

    Body(float x, float y, float width, float height, float vertical_speed, int directionX, int directionY) : 
        rect{ x, y, width, height }, 
        previousRect{ x, y, width, height }, 
        vertical_speed(vertical_speed),
        direction(directionX, directionY)
    {}

    void setPosition(float x, float y)
    {
        rect.x = x;
        rect.y = y;
    }

    void setDirection(int x, int y)
    {
        direction.x = x;
        direction.y = y;
    }

    Direction getDirection() const
    {
        return direction;
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
        previousRect = getRect();
    }
};
