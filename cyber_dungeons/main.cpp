#include "raylib.h"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

struct Body {
    Rectangle rect;
    Rectangle previousRect;
    float vertical_speed;

    Body(float x, float y, float width, float height, float vertical_speed) : 
        rect{ x, y, width, height }, 
        previousRect{ x, y, width, height }, 
        vertical_speed(vertical_speed)
    {}

    void setPosition(float x, float y)
    {
        rect.x = x;
        rect.y = y;
    }

    void setVerticalSpeed(float speed)
    {
        vertical_speed = speed;
    }

    float getVerticalSpeed() const
    {
        return vertical_speed;
    }

    void move(float dx, float dy)
    {
        rect.x += dx;
        rect.y += dy;
    }

    Rectangle getRect() const
    {
        return rect;
    }

    Rectangle getPreviousRect() const
    {
        return previousRect;
    }

    void storePreviousRect()
    {
        previousRect = rect;
    }

};

struct Stats {
    int hp;
    int strength;
    bool isAlive;
    float damageCooldown;
    float damageDashTimer;

    Stats(int hp, int strength, bool isAlive, float damageCooldown, float damageDashTimer) :
        hp(hp), strength(strength), isAlive(isAlive), damageCooldown(damageCooldown), damageDashTimer(damageDashTimer) {}

    void getDamaged(int damage)
    {
        if (damageDashTimer <= 0.0f)
        { 
            hp = hp - damage;
            startDamageCooldown();
        }
    }

    int getHp() const
    {
        return hp;
    }

    int getStrength() const
    {
        return strength;
    }

    void startDamageCooldown()
    {
        damageDashTimer = damageCooldown;
    }

    void decreaseDamageDashTimer()
    {
        if (damageDashTimer >= 0)
        {
            damageDashTimer -= GetFrameTime();
        }
    }

    float getDamageDashTimer() const
    {
        return damageDashTimer;
    }

};

class Player
{
private:
    float speed;
    float max_falling_speed;
    float jumping_speed;
    float gravity;
    Body body;
    Stats stats;

public:
    enum State {
        ON_GROUND,
        JUMPING,
        FALLING,
    };
    Player::State current_state;

    Player(float x, float y, float width, float height) : 
        body(x, y, width, height, 0.f),
        stats(3, 0, true, 2.0f, 0.0f),
        speed(5.f), 
        gravity(0.1f), 
        max_falling_speed(10.f), 
        jumping_speed(-3.f),
        current_state(FALLING) {}

    void render()
    {
        displayDebug();

        if (isDamageInvencibility())
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

    Rectangle getRect()
    {
        return body.getRect();
    }

    Rectangle getPreviousRect()
    {
        return body.getPreviousRect();
    }

    void setPosition(float x, float y)
    {
        body.setPosition(x, y);
    }

    void update()
    {
        storePreviousRect();
        updateSpeed();
        updatePosition();
        updateCooldowns();
    }

    void storePreviousRect()
    {
        body.storePreviousRect();
    }

    void updateSpeed()
    {
        if (body.getVerticalSpeed() < max_falling_speed)
        {
            auto updatedVerticalSpeed = body.getVerticalSpeed() + gravity;
            body.setVerticalSpeed(updatedVerticalSpeed);
        }
    }

    void updatePosition()
    {
        body.move(0, body.getVerticalSpeed());
    }

    void getData() const
    {
        std::cout << "float x_position: " << body.getRect().x << std::endl;
        std::cout << "float y_position: " << body.getRect().y << std::endl;
        std::cout << "width: " << body.getRect().width << std::endl;
        std::cout << "height: " << body.getRect().height << std::endl;
    }

    void input()
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

    void displayDebug() const
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

        DrawText("Player State: ", 20, 20, 16, LIGHTGRAY);
        DrawText(state.c_str(), 150, 20, 16, LIGHTGRAY);

        DrawText("Hp: ", 20, 40, 16, LIGHTGRAY);
        DrawText(std::to_string(stats.getHp()).c_str(), 150, 40, 16, LIGHTGRAY);

        DrawText("Damage Cooldown: ", 20, 60, 16, LIGHTGRAY);
        DrawText(std::to_string(stats.getDamageDashTimer()).c_str(), 150, 60, 16, LIGHTGRAY);
    }

    void setVerticalSpeed(float speed)
    {
        body.setVerticalSpeed(speed);
    }

    float getVerticalSpeed() const
    {
        return body.getVerticalSpeed();
    }

    Rectangle getRect() const
    {
        return body.getRect();
    }

    void setState(enum State state)
    {
        current_state = state;
    }

    enum State getState() const
    {
        return current_state;
    }

    void getDamaged(int damage)
    {
        stats.getDamaged(damage);
    }

    int getHp() const
    {
        return stats.getHp();
    }

    int getStrength() const
    {
        return stats.getStrength();
    }

    void updateCooldowns()
    {
        stats.decreaseDamageDashTimer();
    }

    bool isDamageInvencibility()
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

    bool shouldPlayerBlink(int delay = 10)
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
};

class Enemy
{
private:
    float speed;
    float max_falling_speed;
    float jumping_speed;
    float gravity;
    Body body;
    Stats stats;

public:
    enum State {
        ON_GROUND,
        JUMPING,
        FALLING
    };
    Enemy::State current_state;

    Enemy(float x, float y, float width, float height) : 
        body(x, y, width, height, 0.f),
        stats(1, 1, true, 0.0f, 0.0f),
        speed(5.f), 
        gravity(0.1f), 
        max_falling_speed(10.f), 
        jumping_speed(-3.f),
        current_state(FALLING) {}

    void render() const
    {
        displayDebug();
        DrawRectangle(body.getRect().x, body.getRect().y, body.getRect().width, body.getRect().height, RED);
    }

    Rectangle getRect()
    {
        return body.getRect();
    }

    Rectangle getPreviousRect()
    {
        return body.getPreviousRect();
    }

    void setPosition(float x, float y)
    {
        body.setPosition(x, y);
    }

    void update()
    {
        storePreviousRect();
        updateSpeed();
        updatePosition();
    }

    void storePreviousRect()
    {
        body.storePreviousRect();
    }

    void updateSpeed()
    {
        if (body.getVerticalSpeed() < max_falling_speed)
        {
            auto updatedVerticalSpeed = body.getVerticalSpeed() + gravity;
            body.setVerticalSpeed(updatedVerticalSpeed);
        }
    }

    void updatePosition()
    {
        body.move(0, body.getVerticalSpeed());
    }

    void getData() const
    {
        std::cout << "float x_position: " << body.getRect().x << std::endl;
        std::cout << "float y_position: " << body.getRect().y << std::endl;
        std::cout << "width: " << body.getRect().width << std::endl;
        std::cout << "height: " << body.getRect().height << std::endl;
    }

    void displayDebug() const
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

    void setVerticalSpeed(float speed)
    {
        body.setVerticalSpeed(speed);
    }

    float getVerticalSpeed() const
    {
        return body.getVerticalSpeed();
    }

    Rectangle getRect() const
    {
        return body.getRect();
    }

    void setState(enum State state)
    {
        current_state = state;
    }

    enum State getState() const
    {
        return current_state;
    }

    void getDamaged(int damage)
    {
        stats.getDamaged(damage);
    }

    int getHp() const
    {
        return stats.getHp();
    }

    int getStrength() const
    {
        return stats.getStrength();
    }
};


class Platform
{
public:
    Rectangle rect;

    Platform(float x, float y, float width, float height) : 
        rect{x, y, width, height} {}

    void render() const
    {
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, BLUE);
    }

};

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
    GameManager(Player player, std::vector<Enemy> *enemies, std::vector<Platform> *platforms) : 
        player(player), 
        enemies(enemies),
        platforms(platforms), 
        collided_platform_rect(-1, -1, -1, -1) {}

    void input() {
        player.input();
    }

    void update() {
        std::vector <Enemy> enemiesPreviousRect;

        player.update();

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

    void checkCollisionEntities(Player& player, const Enemy& enemy)
    {
        if (CheckCollisionRecs(player.getRect(), enemy.getRect())) {
            player.getDamaged(enemy.getStrength());
        }
    }

    void render() {
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

    void run() {
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

    bool resolveVerticalFallingCollision(Rectangle currRect, Rectangle prevRect, float verticalSpeed, Platform platform)
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
};


int main()
{
    Player player{ 160, 200, 20, 20 };

    std::vector<Enemy> enemies = {
        Enemy(200, 200, 20, 20),
        Enemy(500, 200, 20, 20),
    };

    std::vector<Platform> platforms = {
        Platform(150, 100, 180, 20),
        Platform(150, 300, 100, 20),
        Platform(250, 400, 100, 20),
        Platform(180, 450, 50, 20),
        Platform(280, 550, 50, 20),
        Platform(450, 540, 100, 20),
        Platform(350, 350, 20, 20),
        Platform(700, 300, 180, 20),
    };
    GameManager game{player, &enemies, &platforms };
    player.getData();
    game.run();

    CloseWindow();

	return 0;
}
