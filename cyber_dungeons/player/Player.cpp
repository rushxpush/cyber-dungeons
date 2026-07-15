#include "Player.h"
#include "Body.h"
#include "Stats.h"
#include "Flags.h"
#include "Coordinates.h"
#include <iostream>
#include <string>

Player::Player(float x, float y, float width, float height) :
    body(x, y, width, height, 0.f),
    stats(3, 3, 0, true, 2.0f, 0.0f, 1.0f, 0.0f),
    speed(5.f), 
    gravity(0.1f), 
    max_falling_speed(10.f), 
    jumping_speed(-3.f),
    current_state(FALLING), 
    flags(true, true, true, true),
    respawnPosition(x, y) {}

void Player::render()
{
    displayDebug();

    if (!isPlayerAlive())
    {
        DrawRectangle(body.getRect().x, body.getRect().y, body.getRect().width, body.getRect().height, DARKGRAY);

        if (shouldPlayerBlink())
        {
            DrawRectangle(body.getRect().x, body.getRect().y, body.getRect().width, body.getRect().height, RED);
        }
    }

    else if (isDamageInvincibility())
    {
        if (shouldPlayerBlink())
        {
            DrawRectangle(body.getRect().x, body.getRect().y, body.getRect().width, body.getRect().height, DARKBLUE);
        }
    }
    else {
        DrawRectangle(body.getRect().x, body.getRect().y, body.getRect().width, body.getRect().height, DARKGREEN);
    }
}

Rectangle Player::getRect() const
{
    return body.getRect();
}

Rectangle Player::getPreviousRect()
{
    return body.getPreviousRect();
}

void Player::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

void Player::update()
{
    storePreviousRect();
    updateSpeed();
    updatePosition();
    updateCooldowns();
    respawn();
}

bool Player::isPlayerAlive() const
{
    return stats.getIsAlive();
}

void Player::getData() const
{
    std::cout << "float x_position: " << body.getRect().x << std::endl;
    std::cout << "float y_position: " << body.getRect().y << std::endl;
    std::cout << "width: " << body.getRect().width << std::endl;
    std::cout << "height: " << body.getRect().height << std::endl;
}

void Player::input()
{
    if (flags.control)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            body.setPosition(body.getRect().x - speed, body.getRect().y);
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            body.setPosition(body.getRect().x + speed, body.getRect().y);
        }
        if (IsKeyDown(KEY_Z))
        {
            if (current_state == State::ON_GROUND)
            {
                setState(State::JUMPING);
                body.setVerticalSpeed(jumping_speed);
            }
        }
    }

}


void Player::setVerticalSpeed(float speed)
{
    body.setVerticalSpeed(speed);
}

float Player::getVerticalSpeed() const
{
    return body.getVerticalSpeed();
}

void Player::setState(enum State state)
{
    current_state = state;
}

Player::State Player::getState() const  
{  
   return current_state;  
}


void Player::getDamaged(int damage)
{
    stats.getDamaged(damage);
}

int Player::getHp() const
{
    return stats.getHp();
}

int Player::getStrength() const
{
    return stats.getStrength();
}


bool Player::isDamageInvincibility()
{
    if (stats.getDamageDashTimer() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::shouldPlayerBlink(int delay)
{
    if ((int)(GetTime() * delay) % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::getIsAlive() const
{
    return stats.isAlive;
}

bool Player::isHpDepleted() const
{
    return stats.hp <= 0 ? true : false;
}

void Player::die()
{
    if (stats.getHp() > 0) stats.setHp(0);
    stats.die();
    stats.startRespawnCooldown();
    stats.resetDamageDashTimer();
    setState(Player::DYING);
    setFlag(PlayerFlag::POSITION, false);
    setFlag(PlayerFlag::CONTROL, false);
}

void Player::respawn()
{

    if (stats.getIsAlive() == false && stats.getRespawnDashTimer() <= 0)
    {
        stats.setIsAlive(true);
        stats.setHp(stats.maxHp);
        setState(Player::FALLING);
        setFlag(PlayerFlag::POSITION, true);
        setFlag(PlayerFlag::CONTROL, true);
        setPosition(respawnPosition.x, respawnPosition.y);
        setVerticalSpeed(0.0f);
    }
}

void Player::setFlag(PlayerFlag flag, bool state)
{
    switch (flag)
    {
    case (PlayerFlag::POSITION):
        flags.position = state;
        break;
    case (PlayerFlag::SPEED):
        flags.speed = state;
        break;
    case (PlayerFlag::GRAVITY):
        flags.gravity = state;
        break;
    case (PlayerFlag::CONTROL):
        flags.control = state;
        break;
    }
}

void Player::storePreviousRect()
{
    body.storePreviousRect();
}

void Player::updateSpeed()
{
    if (body.getVerticalSpeed() < max_falling_speed)
    {
        auto updatedVerticalSpeed = body.getVerticalSpeed() + gravity;
        body.setVerticalSpeed(updatedVerticalSpeed);
    }
}

void Player::updatePosition()
{
    if (flags.position) body.move(0, body.getVerticalSpeed());
}

void Player::updateCooldowns()
{
    stats.decreaseDamageDashTimer();
    stats.decreaseRespawnDashTimer();
}

void Player::displayDebug() const
{
    std::string state;
    if (getState() == State::ON_GROUND)
    {
        state = "ON_GROUND";
    }
    if (getState() == State::FALLING)
    {
        state = "FALLING";
    }
    if (getState() == State::JUMPING)
    {
        state = "JUMPING";
    }
    if (getState() == State::DYING)
    {
        state = "DYING";
    }

    //DrawText("vertical_speed: ", 20, 20, 16, LIGHTGRAY);
    //DrawText(std::to_string(body.getVerticalSpeed()).c_str(), 150, 20, 16, LIGHTGRAY);

    // First Column
    int col1KeyX = 20;
    int col1ValX = 170;
    DrawText("Player State: ", col1KeyX, 20, 16, LIGHTGRAY);
    DrawText(state.c_str(), col1ValX, 20, 16, LIGHTGRAY);

    DrawText("Hp: ", col1KeyX, 40, 16, LIGHTGRAY);
    DrawText(std::to_string(stats.getHp()).c_str(), col1ValX, 40, 16, LIGHTGRAY);

    DrawText("Damage Cooldown: ", col1KeyX, 60, 16, LIGHTGRAY);
    DrawText(std::to_string(stats.getDamageDashTimer()).c_str(), col1ValX, 60, 16, LIGHTGRAY);

    DrawText("Respawn Cooldown: ", col1KeyX, 80, 16, LIGHTGRAY);
    DrawText(std::to_string(stats.getRespawnDashTimer()).c_str(), col1ValX, 80, 16, LIGHTGRAY);

    // Second Column
    int col2KeyX = 300;
    int col2ValX = 470;
    DrawText("isAlive: ", col2KeyX, 20, 16, LIGHTGRAY);

    Color isAliveColor = getIsAlive() ? DARKGREEN : RED;
    DrawText(getIsAlive() ? "true" : "false", col2ValX, 20, 16, isAliveColor);

    DrawText("flags.position: ", col2KeyX, 40, 16, LIGHTGRAY);
    DrawText(flags.position ? "true" : "false", col2ValX, 40, 16, LIGHTGRAY);

    DrawText("flags.control: ", col2KeyX, 60, 16, LIGHTGRAY);
    DrawText(flags.control ? "true" : "false", col2ValX, 60, 16, LIGHTGRAY);
}
