#include <raylib.h>
#include "GameConfig.h"
#include "BackgroundSystem.h"
#include "GameCamera.h"
#include "Background.h"
#include "iostream"

BackgroundSystem::BackgroundSystem(GameConfig *gameConfig, float x, float y) 
{
	referencePoint.x = x;
	referencePoint.y = y;
	BackgroundSystem::gameConfig = gameConfig;

	layers.emplace_back(gameConfig->screenWidth, gameConfig->screenHeight, "resources/images/sky.png", Background::ZPosition::SKY, 0.0f);
	layers.emplace_back(gameConfig->screenWidth, gameConfig->screenHeight, "resources/images/background_far.png", Background::ZPosition::FAR, 0.1f);
    layers.emplace_back(gameConfig->screenWidth, gameConfig->screenHeight, "resources/images/background_medium.png", Background::ZPosition::MEDIUM, 0.2f);
	layers.reserve(1);
	layers.emplace_back(gameConfig->screenWidth, gameConfig->screenHeight, "resources/images/background_near.png", Background::ZPosition::NEAR, 0.3f);
};

void BackgroundSystem::render()
{
	for (const auto& layer : layers)
	{
		BeginMode2D(layer.camera.getCamera());
			layer.background.render();
		EndMode2D();
	}
}

void BackgroundSystem::update()
{
	for (auto& layer : layers)
	{
		layer.camera.setCameraPosition(referencePoint.x * layer.getParallaxFactor(), referencePoint.y * layer.getParallaxFactor(), 0, 0);
	}
}

void BackgroundSystem::setReferencePoint(float x, float y)
{
	referencePoint.x = x;
	referencePoint.y = y;
}
