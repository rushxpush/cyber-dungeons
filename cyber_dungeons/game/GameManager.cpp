#include "GameManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Direction.h"
#include <vector>

GameManager::GameManager(Player player, std::vector<Enemy> *enemies, std::vector<Platform> *platforms) : 
    player(player), 
    enemies(enemies),
    platforms(platforms), 
    collided_platform_rect(-1, -1, -1, -1),
    //state(PLAYING){}
    state(MAIN_MENU){}

void GameManager::input() 
{
    player.input();
}

void GameManager::update() {
    std::vector <Enemy> enemiesPreviousRect;

    player.update();
    checkOffscreenFall(player);

    for (Enemy& enemy : *enemies)
    {
        enemy.update();
    }

    bool isPlayerOnGround = false;
    for (const auto& platform : *platforms)
    {

        if (resolveVerticalCollision(player.getRect(), player.getPreviousRect(), player.getVerticalSpeed(), player.getDirection(), platform))
        {
            if (player.getDirection().y < 0)
            {
                player.setVerticalSpeed(0);
            }
            else if (player.getDirection().y > 0)
            {
                isPlayerOnGround = true;
                player.setState(Player::ON_GROUND);
                player.setVerticalSpeed(0);
                player.setPosition(player.getRect().x, platform.rect.y - player.getRect().height);
            }
        }
        else {
            if (!isPlayerOnGround && player.getState() != Player::FALLING) player.setState(Player::FALLING);
        }

        if (resolveHorizontalCollision(player.getRect(), player.getPreviousRect(), player.getDirection(), platform))
        {
            if (player.getDirection().x < 0)
            {
                player.setPosition(platform.rect.x + platform.rect.width, player.getRect().y);
            }
            else if (player.getDirection().x > 0)
            {
                player.setPosition(platform.rect.x - player.getRect().width, player.getRect().y);
            }

        }
    }

    for (auto& enemy : *enemies)
    {
        checkCollisionEntities(player, enemy);

        bool isEnemyOnGround = false;

        for (const auto& platform : *platforms)
        {
            if (resolveVerticalCollision(enemy.getRect(), enemy.getPreviousRect(), enemy.getVerticalSpeed(), enemy.getDirection(), platform))
            {
                if (enemy.getDirection().y < 0)
                {
                    enemy.setVerticalSpeed(0);
                }
                else if (enemy.getDirection().y > 0)
                {
                    isEnemyOnGround = true;
                    enemy.setState(Enemy::ON_GROUND);
                    enemy.setVerticalSpeed(0);
                    enemy.setPosition(enemy.getRect().x, platform.rect.y - enemy.getRect().height);
                }
            }
            else {
                if (!isEnemyOnGround) enemy.setState(Enemy::FALLING);
            }
        }
    }
}

void GameManager::checkCollisionEntities(Player& player, const Enemy& enemy)
{
    if (CheckCollisionRecs(player.getRect(), enemy.getRect())) {
        player.getDamaged(enemy.getStrength());
        if (player.isHpDepleted() && player.getIsAlive())
        {
            setState(GAME_OVER);
            player.die();
        }
    }
}

void GameManager::checkOffscreenFall(Player& player)
{
    if (player.getRect().y > screenHeight + offscreenDeathTolerance && player.getIsAlive())
    {
        setState(GAME_OVER);
        player.die();
    }
}

void GameManager::render() {
    player.render();

    for (const auto& enemy : *enemies)
    {
        enemy.render();
    }

    for (const auto& platform : *platforms)
    {
        platform.render();
    }
}

void GameManager::run() {
    InitWindow(screenWidth, screenHeight, "Cyber Dungeons!");
    SetTargetFPS(60);
    isRunning = true;

    while (!WindowShouldClose() && isRunning)
    {
        switch (state)
        {
            case MAIN_MENU:
                runMainMenuState();
            break;
            case PLAYING:
                runPlayingState();
                break;
            case GAME_OVER:
                runGameOverState();
                break;
            default:
                break;
        }
    }
}

void GameManager::restart()
{
    setState(PLAYING);
    player.restart();
}

void GameManager::setState(GameManager::State newState)
{
    state = newState;
}

GameManager::State GameManager::getState()
{
    return state;
}

void GameManager::runMainMenuState()
{
    if (GetKeyPressed() > 0)
    {
        startGame();
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        const char* titleText = "Cyber Dungeons";
        int titleFontSize = 40;
        DrawText(titleText, (screenWidth - MeasureText(titleText, titleFontSize)) / 2, (screenHeight - 100) / 2, titleFontSize, BLUE);


        const char* subtitleText = "Press any key to start game";
        int subtitleFontSize = 20;
        DrawText(subtitleText, (screenWidth - MeasureText(subtitleText, subtitleFontSize)) / 2, (screenHeight + 40) / 2, subtitleFontSize, DARKBLUE);
    EndDrawing();
}

void GameManager::runPlayingState()
{
    input();
    update();
    BeginDrawing();
        ClearBackground(RAYWHITE);
        render();
    EndDrawing();
}

void GameManager::runGameOverState()
{
    if (GetKeyPressed() > 0)
    {
        restart();
    }
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Game Over", 20, 200, 20, RED);
        DrawText("Press any key to restart...", 20, 220, 20, RED);
        render();
    EndDrawing();
}

void GameManager::startGame()
{
    setState(PLAYING);
}

bool GameManager::resolveVerticalCollision(Rectangle currRect, Rectangle prevRect, float verticalSpeed, Direction direction, Platform platform)
{
    const bool isRectHorizontallyAligned = currRect.x + currRect.width > platform.rect.x
        && currRect.x < platform.rect.x + platform.rect.width;

    const Rectangle currentPlayerRect = currRect;
    const float currentRectBottom = currentPlayerRect.y + currentPlayerRect.height;
    const float previousRectBottom = prevRect.y + prevRect.height;
    const float platformTop = platform.rect.y;

    const float currentRectTop = currentPlayerRect.y;
    const float previousRectTop = prevRect.y;
    const float platformBottom = platform.rect.y + platform.rect.height;

    if (isRectHorizontallyAligned
        && previousRectTop  >= platformBottom 
        && currentRectTop  < platformBottom 
        && direction.y < 0 
        )
    {
        return true;
    }
    else if (isRectHorizontallyAligned
        && previousRectBottom <= platform.rect.y
        && currentRectBottom > platform.rect.y
        && direction.y > 0
        )
    {
        return true;
    }

    return false;
}

bool GameManager::resolveHorizontalCollision(Rectangle currRect, Rectangle prevRect, Direction direction, Platform platform)
{
    const bool isRectVerticallyAligned = currRect.y + currRect.height > platform.rect.y
        && currRect.y < platform.rect.y + platform.rect.height;


    const Rectangle currentPlayerRect = currRect;
    if (direction.x > 0)
    {
        const float currentRectRight = currentPlayerRect.x + currentPlayerRect.width;
        const float previousRectRight = prevRect.x + prevRect.width;
        const float platformLeft = platform.rect.x;

        if (isRectVerticallyAligned
            && previousRectRight <= platformLeft
            && currentRectRight > platformLeft)
        {
            return true;
        }
        return false;
    }
    else if (direction.x < 0)
    {
        const float currentRectLeft = currentPlayerRect.x;
        const float previousRectLeft = prevRect.x;
        const float platformRight = platform.rect.x + platform.rect.width;

        if (isRectVerticallyAligned
            && previousRectLeft >= platformRight
            && currentRectLeft < platformRight)
        {
            return true;
        }
        return false;
    }
}
