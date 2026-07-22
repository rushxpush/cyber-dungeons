#pragma once

#include <raylib.h>
#include <vector>
#include "GameConfig.h"
#include "Action.h"
#include "Button.h"

class MainMenu
{
private:
	GameConfig& config;
	const int screenWidth = 800;
    const int screenHeight = 600;
	Action action;
	std::vector<Button>& options;

public:
	MainMenu(GameConfig& config, std::vector<Button>& options);

	void render();

	void update();

	void input();

	void setAction(Action newAction);

	Action getAction() const;

	void renderOption(Button button);
};
