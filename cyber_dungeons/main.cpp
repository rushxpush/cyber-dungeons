#include "raylib.h"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include "GameManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Body.h"
#include "Stats.h"
#include "Flags.h"

int main()
{
    Player player{ 160, 200, 20, 20, 0, 0 };

    std::vector<Enemy> enemies = {
        Enemy(200, 200, 20, 20, 0, 0),
        Enemy(500, 200, 20, 20, 0, 0),
    };

    std::vector<Platform> platforms = {
        Platform(150, 100, 180, 20),
        Platform(150, 300, 100, 20),
        Platform(250, 280, 100, 20),
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
