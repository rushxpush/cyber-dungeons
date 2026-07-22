#include "raylib.h"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include "GameConfig.h"
#include "GameManager.h"
#include "MainMenu.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Body.h"
#include "Stats.h"
#include "Flags.h"
#include "Button.h"

int main()
{
    GameConfig config{ 800, 600, "Cyber Dungeons!" };

    //struct ButtonData {
    //    Vector2 position;
    //    int width;
    //    int height;
    //    const char* text;
    //};

    struct ButtonData {
        //Vector2 position;
        //int width;
        //int height;
        Rectangle rect;
        const char* text;
        Action action;

        ButtonData(int x, int y, int width, int height, const char* text, Action action) :
            rect(x, y, width, height),
            text(text),
            action(action) {}
    };

    const int buttonWidth = 300;
    const int buttonHeight = 50;
    const int buttonSpacing = 50;
    ButtonData button1(
        (config.screenWidth / 2) - (buttonWidth / 2),
        (config.screenHeight / 2) - (buttonHeight / 2) - buttonHeight - buttonSpacing,
        buttonWidth,
        buttonHeight,
        "Start Game",
        Action::START_GAME
    );

    ButtonData button2(
        (config.screenWidth / 2) - (buttonWidth / 2),
        (config.screenHeight / 2) - (buttonHeight / 2),
        buttonWidth,
        buttonHeight,
        "Options",
        Action::ENTER_SETTINGS
    );
    ButtonData button3(
        (config.screenWidth / 2) - (buttonWidth / 2),
        (config.screenHeight / 2) - (buttonHeight / 2) + buttonHeight + buttonSpacing,
        buttonWidth,
        buttonHeight,
        "Exit Game",
        Action::EXIT_GAME
    );

    std::vector<ButtonData> buttonsList = {
        button1,
        button2,
        button3
    };

    std::vector<Button> options;
    for (int i = 0; i < buttonsList.size(); i++)
    {
        options.push_back(
            Button(
                buttonsList[i].rect.x, 
                buttonsList[i].rect.y, 
                buttonsList[i].rect.width, 
                buttonsList[i].rect.height, 
                GRAY, 
                buttonsList[i].text,
                BLACK, 
                20.f, 
                0,
                buttonsList[i].action
            )
        );
    }

    MainMenu mainMenu{ config, options };

    Player player{ 160, 200, 20, 20, 0, 0 };

    std::vector<Enemy> enemies = {
        Enemy(200, 200, 20, 20, 0, 0),
        Enemy(500, 500, 20, 20, 0, 0),
    };

    std::vector<Platform> platforms = {
        Platform(150, 100, 180, 20),
        Platform(150, 300, 100, 20),
        Platform(250, 280, 100, 20),
        Platform(250, 400, 100, 20),
        Platform(180, 450, 50, 20),
        Platform(500, 475, 50, 20),
        Platform(280, 550, 50, 20),
        Platform(450, 540, 100, 20),
        Platform(350, 350, 20, 20),
        Platform(700, 300, 180, 20),
    };
    GameManager game{ config, mainMenu, player, &enemies, &platforms };
    player.getData();
    game.run();

    CloseWindow();

	return 0;
}
