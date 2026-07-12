#pragma once

#include "Body.h"
#include "Stats.h"
#include "Flags.h"

class Enemy
{
private:
    float speed;
    float max_falling_speed;
    float jumping_speed;
    float gravity;

    Body body;
    Stats stats;
    Flags flags;

public:
    enum State {
        ON_GROUND,
        JUMPING,
        FALLING
    };
    Enemy::State current_state;

    Enemy(float x, float y, float width, float height);

    // core
    void render() const;
    void update();

    // lifecycle

    // state
    void setState(enum State state);
    enum State getState() const;

    // collision
    Rectangle getRect() const;
    Rectangle getPreviousRect() const;

    // movement
    void setPosition(float x, float y);
    void setVerticalSpeed(float speed);
    float getVerticalSpeed() const;

    // stats
    void getDamaged(int damage);
    int getHp() const;
    int getStrength() const;

    // helpers

private:
    void storePreviousRect();
    void updateSpeed();
    void updatePosition();
    void getData() const;
    void displayDebug() const;

};
