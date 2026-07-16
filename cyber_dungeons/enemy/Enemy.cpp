#include "Enemy.h"
#include "Body.h"
#include "Stats.h"
#include "Flags.h"
#include <iostream>


Enemy::Enemy(float x, float y, float width, float height, int directionX, int directionY) : 
    body(x, y, width, height, 0.f, directionX, directionY),
    stats(1, 1, 1, true, 0.0f, 0.0f, 0.0f, 0.0f),
    speed(5.f), 
    gravity(0.1f), 
    max_falling_speed(10.f), 
    jumping_speed(-3.f),
    current_state(FALLING), 
    flags(true, true, true, false) {}

void Enemy::render() const
{
    displayDebug();
    DrawRectangle(body.getRect().x, body.getRect().y, body.getRect().width, body.getRect().height, RED);
}

Rectangle Enemy::getRect() const
{
    return body.getRect();
}

Rectangle Enemy::getPreviousRect() const
{
    return body.getPreviousRect();
}

void Enemy::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

void Enemy::update()
{
    storePreviousRect();

            if (current_state == State::ON_GROUND)
            {
                setState(State::JUMPING);
                body.setVerticalSpeed(jumping_speed);
            }
    updateSpeed();
    updateDirection();
    updatePosition();
}

void Enemy::storePreviousRect()
{
    body.storePreviousRect();
}

void Enemy::updateSpeed()
{
    if (body.getVerticalSpeed() < max_falling_speed)
    {
        auto updatedVerticalSpeed = body.getVerticalSpeed() + gravity;
        body.setVerticalSpeed(updatedVerticalSpeed);
    }
}

void Enemy::updatePosition()
{
    body.move(0, body.getVerticalSpeed());
}

void Enemy::getData() const
{
    std::cout << "float x_position: " << body.getRect().x << std::endl;
    std::cout << "float y_position: " << body.getRect().y << std::endl;
    std::cout << "width: " << body.getRect().width << std::endl;
    std::cout << "height: " << body.getRect().height << std::endl;
}

void Enemy::displayDebug() const
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
    //DrawText("vertical_speed: ", 20, 20, 16, LIGHTGRAY);
    //DrawText(std::to_string(body.getVerticalSpeed()).c_str(), 150, 20, 16, LIGHTGRAY);

    //DrawText("Enemy State: ", 20, 40, 16, LIGHTGRAY);
    //DrawText(state.c_str(), 150, 40, 16, LIGHTGRAY);
}

Direction Enemy::getDirection() const
{
    return body.getDirection();
}

void Enemy::updateDirection()
{
    if (body.getVerticalSpeed() < 0)
    {
        body.setDirection(body.getDirection().x, -1);
    }
    else if (body.getVerticalSpeed() > 0)
    {
        body.setDirection(body.getDirection().x , 1);
    }
    else {
        body.setDirection(body.getDirection().x, 0);
    }
}


void Enemy::setVerticalSpeed(float speed)
{
    body.setVerticalSpeed(speed);
}

float Enemy::getVerticalSpeed() const
{
    return body.getVerticalSpeed();
}

void Enemy::setState(enum State state)
{
    current_state = state;
}

enum Enemy::State Enemy::getState() const
{
    return current_state;
}

void Enemy::getDamaged(int damage)
{
    stats.getDamaged(damage);
}

int Enemy::getHp() const
{
    return stats.getHp();
}

int Enemy::getStrength() const
{
    return stats.getStrength();
}
