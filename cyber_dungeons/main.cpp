#include "raylib.h"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

class Player
{
private:
    float speed;
    float y_speed;
    float max_terminal_y_speed;
    float gravity;

public:
    enum State {
        ON_GROUND,
        JUMPING,
        FALLING
    };
    Player::State currentState;
    Rectangle rect;
    Player(float x, float y, float width, float height) : rect{x, y, width, height}, speed(5.f), y_speed(0.f), gravity(0.1f), max_terminal_y_speed(10.f), currentState(FALLING) {}

    void render() const
    {
        displayDebug();
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, RED);
    }

    void update()
    {

        updateSpeed();
        updatePosition();

    }

    void updateSpeed()
    {
        if (y_speed < max_terminal_y_speed)
        {
            y_speed += gravity;
        }
    }

    void updatePosition()
    {
        rect.y += y_speed;
    }

    void getData() const
    {
        std::cout << "float x_position: " << rect.x << std::endl;
        std::cout << "float y_position: " << rect.y << std::endl;
        std::cout << "width: " << rect.width << std::endl;
        std::cout << "height: " << rect.height << std::endl;
    }

    void input()
    {
        if (IsKeyDown(KEY_LEFT))
        {
            rect.x = rect.x - speed;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            rect.x = rect.x + speed;
        }
        if (IsKeyDown(KEY_SPACE))
        {
            // TO DO
        }
    }

    void displayDebug() const
    {
        DrawText("vertical_speed: ", 20, 20, 16, LIGHTGRAY);
        DrawText(std::to_string(y_speed).c_str(), 150, 20, 16, LIGHTGRAY);
    }

    void setYSpeed(float speed)
    {
        y_speed = speed;
    }

    float getYSpeed() const
    {
        return y_speed;
    }

    Rectangle getRect() const
    {
        return rect;
    }

    void setState(enum State state)
    {
        currentState = state;
    }

    enum State getState() const
    {
        return currentState;
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
    Rectangle collided_platform_rect;

public:
    GameManager(Player player, std::vector <Platform> *platforms) : player(player), platforms(platforms), collided_platform_rect(-1, -1, -1, -1) {}

    void input() {
        player.input();
    }

    void update() {
        const Rectangle playerPreviousRect = player.getRect();

        player.update();

        for (const auto& platform : *platforms)
        {
            if (resolveVerticalFallingCollision(player, platform, playerPreviousRect))
            {
                    player.setState(Player::ON_GROUND);
                    player.setYSpeed(0);
                    player.rect.y = platform.rect.y - player.rect.height;
                    setCollidedPlatformRect(platform.rect);
            }
        }
        if (!isPlayerStillOnPlatform(player.rect, collided_platform_rect))
        {
            player.setState(Player::FALLING);
        }
    }

    void render() {
       player.render();

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

    bool resolveVerticalFallingCollision(Player player, Platform platform, Rectangle previousPlayerRect)
    {
        const bool isPlayerHorizontallyAligned = player.rect.x + player.rect.width > platform.rect.x
            && player.rect.x < platform.rect.x + platform.rect.width;

        const Rectangle currentPlayerRect = player.getRect();
        const float currentPlayerBottom = currentPlayerRect.y + currentPlayerRect.height;
        const float previousPlayerBottom = previousPlayerRect.y + previousPlayerRect.height;
        const float platformTop = platform.rect.y;

        if (isPlayerHorizontallyAligned
            && previousPlayerBottom  <= platform.rect.y
            && currentPlayerBottom  > platform.rect.y
            && player.getYSpeed() > 0
           )
        {
            return true;
        }

        return false;
    }

    void setCollidedPlatformRect(Rectangle rect)
    {
        collided_platform_rect = rect;
    }

    bool isPlayerStillOnPlatform(Rectangle player_rect, Rectangle collided_plaform_rect)
    {
        if (!(player_rect.x + player_rect.width > collided_platform_rect.x && player_rect.x < collided_platform_rect.x + collided_platform_rect.width))
        {
            return false;
        }
        return true;
    }
};


int main()
{
    Player player{ 200, 200, 20, 20 };
    std::vector<Platform> platforms = {
        Platform(150, 300, 100, 20),
        Platform(350, 500, 100, 20),
    };
    GameManager game{player, &platforms};
    player.getData();
    game.run();

    CloseWindow();

	return 0;
}
