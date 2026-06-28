#include "raylib.h"
#include <iostream>
#include <string>

class Player
{
    float x_position;
    float y_position;
    float width;
    float height;

    float speed;
    float y_speed;
    float max_terminal_y_speed;
    float gravity;

public:
    Player(float x, float y, float width, float height) : x_position(x), y_position(y), width(width), height(height), speed(5), y_speed(0), gravity(0.1), max_terminal_y_speed(10) {}

    void render()
    {
        displayDebug();
        DrawRectangle(x_position, y_position, width, height, RED);
    }

    void update()
    {
        if (y_speed >= max_terminal_y_speed)
        {
            y_speed = max_terminal_y_speed;
        }
        else
        {
            y_speed += gravity;
        }

        updatePosition();
    }

    void updatePosition()
    {
        y_position += y_speed;
    }

    void getData() const
    {
        std::cout << "float x_position: " << x_position << std::endl;
        std::cout << "float y_position: " << y_position << std::endl;
        std::cout << "width: " << width << std::endl;
        std::cout << "height: " << height << std::endl;
    }

    void input()
    {
        if (IsKeyDown(KEY_LEFT))
        {
            x_position = x_position - speed;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            x_position = x_position + speed;
        }
        if (IsKeyDown(KEY_SPACE))
        {
            // TO DO
        }
    }

    void displayDebug()
    {
        DrawText("vertical_speed: ", 20, 20, 16, LIGHTGRAY);
        DrawText(std::to_string(y_speed).c_str(), 150, 20, 16, LIGHTGRAY);
    }

};

class GameManager
{
private:
	const int screenWidth = 800;
    const int screenHeight = 600;
    bool isRunning = false;
    Player player;


public:
    GameManager(Player player) : player(player) {}

    void input() {
        player.input();
    }

    void update() {
        player.update();
    }

    void render() {
        player.render();
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
};

int main()
{


    Player player{ 200, 200, 20, 20 };
    GameManager game{player};
    player.getData();
    game.run();

    CloseWindow();

	return 0;
}