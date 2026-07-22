#include <raylib.h>
#include <vector>
#include "GameConfig.h"
#include "MainMenu.h"
#include "Button.h"

MainMenu::MainMenu(GameConfig& config, std::vector<Button>& options) :
		config(config),
		action(Action::NONE),
		options(options) {};

void MainMenu::render()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        //const char* titleText = "Cyber Dungeons";
        //int titleFontSize = 40;
        //DrawText(titleText, (screenWidth - MeasureText(titleText, titleFontSize)) / 2, (screenHeight - 100) / 2, titleFontSize, BLUE);

        //const char* subtitleText = "Press any key to start game";
        //int subtitleFontSize = 20;
        //DrawText(subtitleText, (screenWidth - MeasureText(subtitleText, subtitleFontSize)) / 2, (screenHeight + 40) / 2, subtitleFontSize, DARKBLUE);

        for (int i = 0; i < options.size(); i++)
        {
            options[i].render();
        }
    EndDrawing();
}

void MainMenu::update()
{
    Vector2 mousePosition = GetMousePosition();

    for (int i = 0; i < options.size(); i++)
    {
        if (CheckCollisionPointRec(mousePosition, options[i].getRect()))
        {
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                options[i].setState(Button::ButtonState::HOVERED);
                switch (options[i].action)
                {
                    case Action::START_GAME:
                        setAction(Action::START_GAME);
                        break;
                    case Action::ENTER_SETTINGS:
                        setAction(Action::ENTER_SETTINGS);
                        break;
                    case Action::EXIT_GAME:
                        setAction(Action::EXIT_GAME);
                        break;
                }
            }
            else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                options[i].setState(Button::ButtonState::PRESSED);
            }
            else
            {
                options[i].setState(Button::ButtonState::HOVERED);
            }
        }
        else
        {
            options[i].setState(Button::ButtonState::DEFAULT);
        }
    }

}

void MainMenu::input()
{

}

void MainMenu::setAction(Action newAction)
{
    action = newAction;
}

Action MainMenu::getAction() const
{
    return action;
}

void MainMenu::renderOption(Button button)
{
    //DrawRectangle(button.getRect().x, button.getRect().y, button.getRect().width, button.getRect().height, button.getButtonColor());
    //DrawText(button.getText(), button.getRect().x, button.getRect().y, 20, button.getTextColor());
}
