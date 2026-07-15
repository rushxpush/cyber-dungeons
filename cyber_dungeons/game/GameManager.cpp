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
    collided_platform_rect(-1, -1, -1, -1) {}

void GameManager::input() {
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

        if (resolveVerticalFallingCollision(player.getRect(), player.getPreviousRect(), player.getVerticalSpeed(), platform))
        {
            isPlayerOnGround = true;
            player.setState(Player::ON_GROUND);
            player.setVerticalSpeed(0);
            player.setPosition(player.getRect().x, platform.rect.y - player.getRect().height);

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
            if (resolveVerticalFallingCollision(enemy.getRect(), enemy.getPreviousRect(), enemy.getVerticalSpeed(), platform))
            {
                isEnemyOnGround = true;
                enemy.setState(Enemy::ON_GROUND);
                enemy.setVerticalSpeed(0);
                enemy.setPosition(enemy.getRect().x, platform.rect.y - enemy.getRect().height);

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
        if (player.isHpDepleted() && player.getIsAlive()) player.die();
    }
}

void GameManager::checkOffscreenFall(Player& player)
{
    if (player.getRect().y > screenHeight + offscreenDeathTolerance && player.getIsAlive()) player.die();
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
        input();
        update();
        BeginDrawing();
            ClearBackground(RAYWHITE);
            //DrawText("Works", 20, 200, 20, LIGHTGRAY);
            render();
        EndDrawing();
    }
}

bool GameManager::resolveVerticalFallingCollision(Rectangle currRect, Rectangle prevRect, float verticalSpeed, Platform platform)
{
    const bool isRectHorizontallyAligned = currRect.x + currRect.width > platform.rect.x
        && currRect.x < platform.rect.x + platform.rect.width;

    const Rectangle currentPlayerRect = currRect;
    const float currentRectBottom = currentPlayerRect.y + currentPlayerRect.height;
    const float previousRectBottom = prevRect.y + prevRect.height;
    const float platformTop = platform.rect.y;

    if (isRectHorizontallyAligned
        && previousRectBottom  <= platform.rect.y
        && currentRectBottom  > platform.rect.y
        && verticalSpeed > 0
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
