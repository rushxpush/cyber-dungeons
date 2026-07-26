#include <raylib.h>
#include "BackgroundSystem.h"
#include "GameCamera.h"
#include "Background.h"

BackgroundSystem::BackgroundSystem(float x, float y) 
{
	referencePoint.x = x;
	referencePoint.y = y;
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
		switch (layer.zPosition)
		{
		case ZPosition::SKY:
			break;
		case ZPosition::FAR:
			layer.camera.setCameraPosition(referencePoint.x * 0.1, referencePoint.y * 0.1, 0, 0);
			break;
		case ZPosition::MEDIUM:
			layer.camera.setCameraPosition(referencePoint.x * 0.2, referencePoint.y * 0.2, 0, 0);
			break;
		case ZPosition::NEAR:
			layer.camera.setCameraPosition(referencePoint.x * 0.3, referencePoint.y * 0.3, 0, 0);
			break;
		}
	}
}

void BackgroundSystem::setReferencePoint(float x, float y)
{
	referencePoint.x = x;
	referencePoint.y = y;
}

void BackgroundSystem::createLayer(GameCamera camera, Background background, ZPosition zPosition)
{
	Layer layer = Layer{ camera, background, zPosition };
	layers.emplace_back(layer);
}

void BackgroundSystem::destroyLayers()
{
	for (const auto& layer : layers)
	{
		layer.background.destroy();
	}
}

