#pragma once

#include <raylib.h>
#include <vector>
#include "Layer.h"
#include "GameConfig.h"
#include "Background.h"
#include "GameCamera.h"

class BackgroundSystem
{
private:
	const GameConfig* gameConfig;
	GameCamera camera;
	std::vector<Layer> layers;
	Vector2 referencePoint;
	
public:
	BackgroundSystem(GameConfig* gameConfig, float x, float y);

	// core
	void render();
	void update();

	void setReferencePoint(float x, float y);
};
