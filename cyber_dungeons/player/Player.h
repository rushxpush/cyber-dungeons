#pragma once

#include "Body.h"
#include "Stats.h"
#include "Flags.h"
#include "Coordinates.h"

class Player
{
private:
    float speed;
    float max_falling_speed;
    float jumping_speed;
    float gravity;

    Body body;
    Stats stats;
    Flags flags;
    Coordinates respawnPosition;

    Texture2D texture;

public:
    enum State {
        ON_GROUND,
        JUMPING,
        FALLING,
        DYING
    };
    enum PlayerFlag {
        POSITION,
        SPEED,
        GRAVITY,
        CONTROL,
    };
    Player::State current_state;

    Player(float x, float y, float width, float height, int directionX, int directionY);

    // core
    void input();
    void update();
    void render();
    void destroy() const;

    // lifecycle
    void die();
    void respawn();
    void restart();
    
    // state 
    void setState(enum State state);
    enum State getState() const;

    // collision
    Rectangle getRect() const;
    Rectangle getPreviousRect();

    // movement
    void setPosition(float x, float y);
    void setVerticalSpeed(float speed);
    float getVerticalSpeed() const;
    Direction getDirection() const;
    void setDirection(int x, int y);

    // stats
    bool isPlayerAlive() const;
    void getDamaged(int damage);
    int getHp() const;
    int getStrength() const;
    void updateCooldowns();

    // helpers
    bool getIsAlive() const;
    bool isHpDepleted() const;
    bool isDamageInvincibility();
    bool shouldPlayerBlink(int delay = 10);

    void getData() const;
private:
    void storePreviousRect();
    void updateSpeed();
    void updatePosition();
    void updateDirection();
    void displayDebug() const;
    void setFlag(PlayerFlag flag, bool state);
};
