#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include <vector>

class GameManager
{
private:
	const int screenWidth = 800;
    const int screenHeight = 600;
    bool isRunning = false;
    Player player;
    std::vector <Platform> *platforms;
    std::vector <Enemy>* enemies;
    Rectangle collided_platform_rect;

public:
    GameManager(Player player, std::vector<Enemy>* enemies, std::vector<Platform>* platforms);

    // core
    void input();
    void update();
    void render();
    void run();

    // collision
    void checkCollisionEntities(Player& player, const Enemy& enemy);
    bool resolveVerticalFallingCollision(Rectangle currRect, Rectangle prevRect, float verticalSpeed, Platform platform);
};
