#pragma once

#include <raylib.h>
#include "Background.h"
#include "GameCamera.h"
#include <vector>

class BackgroundSystem
{
public:
	enum ZPosition
	{
		NONE,
		SKY,
		FAR,
		MEDIUM,
		NEAR
	};

private:
	struct Layer {
		GameCamera camera;
		Background background;
		ZPosition zPosition;

		Layer(GameCamera camera, Background background, ZPosition zPosition) :
			camera(camera),
			background(background),
			zPosition(zPosition) {}
	};

	std::vector<Layer> layers;
	Vector2 referencePoint;
	
public:
	BackgroundSystem(float x, float y);

	// core
	void render();
	void update();

	void setReferencePoint(float x, float y);

	void createLayer(GameCamera camera, Background background, ZPosition zPosition);

	void destroyLayers();
};
