#pragma once

#include "GameConfig.h"
#include "BackgroundSystem.h"
#include "MainMenu.h"
#include "Background.h"
#include "GameCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include <vector>
#include <unordered_map>

class GameManager
{
private:
    GameConfig config;
	//const int screenWidth;
    //const int screenHeight;
    const int offscreenDeathTolerance = 20;
    bool isRunning = false;
    BackgroundSystem backgroundSystem;
    Player player;
    std::vector <Platform>* platforms;
    std::vector <Enemy>* enemies;
    MainMenu mainMenu;
    GameCamera mainCamera;
    Rectangle collided_platform_rect;
    enum State {
        MAIN_MENU,
        PLAYING,
        GAME_OVER,
        EXIT_GAME
    };
    GameManager::State state;

public:
    GameManager
    (
        GameConfig config, 
        GameCamera mainCamera,
        BackgroundSystem backgroundSystem,
        MainMenu mainMenu, 
        Player player, 
        std::vector<Enemy>* enemies, 
        std::vector<Platform>* platforms
    );

    // core
    void input();
    void update();
    void render();
    void renderPlayingState();
    void run();
    void destroy();

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
