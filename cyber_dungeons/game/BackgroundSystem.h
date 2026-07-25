#pragma once

#include "Background.h"
#include "GameCamera.h"
#include <vector>

class BackgroundSystem
{
private:
	struct Layer {
		GameCamera camera;
		Background background;

		Layer(GameCamera camera, Background background) :
			camera(camera),
			background(background) {}
	};

	std::vector<Layer> layers;
	
public:
	BackgroundSystem();

	// core
	void render();
	void update();

	void createLayer(GameCamera camera, Background background);

	void destroyLayers();
};
