#include "raylib.h"

int main()
{
	const int screenWidth = 800;

    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Cyber Dungeons!");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Works", 20, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

	return 0;
}