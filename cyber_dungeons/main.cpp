#include "raylib.h"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

struct Body {
    Rectangle rect;
    float vertical_speed;

    Body(float x, float y, float width, float height, float vertical_speed) : 
        rect{ x, y, width, height }, 
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

};

class Player
{
private:
    float speed;
    float max_falling_speed;
    float jumping_speed;
    float gravity;
    Body body;

public:
    enum State {
        ON_GROUND,
        JUMPING,
        FALLING
    };
    Player::State current_state;

    Player(float x, float y, float width, float height) : 
        body(x, y, width, height, 0.f),
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

    void setPosition(float x, float y)
    {
        body.setPosition(x, y);
    }

    void update()
    {
        updateSpeed();
        updatePosition();
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
        //DrawText("vertical_speed: ", 20, 20, 16, LIGHTGRAY);
        //DrawText(std::to_string(body.getVerticalSpeed()).c_str(), 150, 20, 16, LIGHTGRAY);
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
                    player.setVerticalSpeed(0);
                    player.setPosition(player.getRect().x, platform.rect.y - player.getRect().height);

                    setCollidedPlatformRect(platform.rect);
            }
        }
        if (!isPlayerStillOnPlatform(player.getRect(), collided_platform_rect))
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
        const bool isPlayerHorizontallyAligned = player.getRect().x + player.getRect().width > platform.rect.x
            && player.getRect().x < platform.rect.x + platform.rect.width;

        const Rectangle currentPlayerRect = player.getRect();
        const float currentPlayerBottom = currentPlayerRect.y + currentPlayerRect.height;
        const float previousPlayerBottom = previousPlayerRect.y + previousPlayerRect.height;
        const float platformTop = platform.rect.y;

        if (isPlayerHorizontallyAligned
            && previousPlayerBottom  <= platform.rect.y
            && currentPlayerBottom  > platform.rect.y
            && player.getVerticalSpeed() > 0
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

    bool isPlayerStillOnPlatform(Rectangle player_rect, Rectangle collided_plaform_rect) const
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
        Platform(150, 100, 180, 20),
        Platform(150, 300, 100, 20),
        Platform(250, 400, 100, 20),
        Platform(180, 450, 50, 20),
        Platform(280, 550, 50, 20),
        Platform(450, 540, 100, 20),
        Platform(350, 350, 20, 20),
        Platform(700, 300, 180, 20),
    };
    GameManager game{player, &platforms};
    player.getData();
    game.run();

    CloseWindow();

	return 0;
}
