#include <raylib.h>
#include "BackgroundSystem.h"
#include "GameCamera.h"
#include "Background.h"

BackgroundSystem::BackgroundSystem() {};

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
	// 
}

void BackgroundSystem::createLayer(GameCamera camera, Background background)
{
	Layer layer = Layer{ camera, background };
	layers.emplace_back(layer);
}

void BackgroundSystem::destroyLayers()
{
	for (const auto& layer : layers)
	{
		layer.background.destroy();
	}
}

