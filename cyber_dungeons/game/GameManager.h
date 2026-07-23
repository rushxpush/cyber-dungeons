#pragma once

#include "GameConfig.h"
#include "MainMenu.h"
#include "GameCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include <vector>

class GameManager
{
private:
    GameConfig config;
	const int screenWidth = 800;
    const int screenHeight = 600;
    const int offscreenDeathTolerance = 20;
    bool isRunning = false;
    Player player;
    std::vector <Platform>* platforms;
    std::vector <Enemy>* enemies;
    MainMenu mainMenu;
    GameCamera camera;
    Rectangle collided_platform_rect;
    enum State {
        MAIN_MENU,
        PLAYING,
        GAME_OVER,
        EXIT_GAME
    };
    GameManager::State state;

public:
    GameManager(GameConfig config, MainMenu mainMenu, Player player, std::vector<Enemy>* enemies, std::vector<Platform>* platforms, GameCamera camera);

    // core
    void input();
    void update();
    void render();
    void renderPlayingState();
    void run();

    // state
    State getState();
    void runMainMenuState();
    void runPlayingState();
    void runGameOverState();
    void runExitGameState();
    void setState(GameManager::State state);
    void startGame();
    void restart();
    void exitGame();

    // collision
    void checkCollisionEntities(Player& player, const Enemy& enemy);
    bool resolveVerticalCollision(Rectangle currRect, Rectangle prevRect, float verticalSpeed, Direction direction, Platform platform);
    bool resolveHorizontalCollision(Rectangle currRect, Rectangle prevRect, Direction direction, Platform platform);
    void checkOffscreenFall(Player& player);
};
