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

    Player(float x, float y, float width, float height);

    // core
    void input();
    void update();
    void render();

    // lifecycle
    void die();
    void respawn();
    
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
    void displayDebug() const;
    void setFlag(PlayerFlag flag, bool state);
};
