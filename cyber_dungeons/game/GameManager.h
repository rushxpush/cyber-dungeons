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
    const int offscreenDeathTolerance = 20;
    bool isRunning = false;
    Player player;
    std::vector <Platform> *platforms;
    std::vector <Enemy>* enemies;
    Rectangle collided_platform_rect;
    enum State {
        MAIN_MENU,
        PLAYING,
        GAME_OVER,
    };
    GameManager::State state;

public:
    GameManager(Player player, std::vector<Enemy>* enemies, std::vector<Platform>* platforms);

    // core
    void input();
    void update();
    void render();
    void run();

    // state
    State getState();
    void runMainMenuState();
    void runPlayingState();
    void runGameOverState();
    void setState(GameManager::State state);
    void startGame();
    void restart();

    // collision
    void checkCollisionEntities(Player& player, const Enemy& enemy);
    bool resolveVerticalCollision(Rectangle currRect, Rectangle prevRect, float verticalSpeed, Direction direction, Platform platform);
    bool resolveHorizontalCollision(Rectangle currRect, Rectangle prevRect, Direction direction, Platform platform);
    void checkOffscreenFall(Player& player);
};
