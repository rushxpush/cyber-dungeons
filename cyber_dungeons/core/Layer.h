#pragma once

#include "Background.h"
#include "GameCamera.h"
#include "iostream"

struct Layer
{
	Background background;
	GameCamera camera;
	float parallaxFactor;

	Layer(
		int screenWidth, 
		int screenHeight, 
		const char* imagePath, 
		Background::ZPosition zPosition, 
		float parallaxFactor
	) : 
		background(screenWidth, screenHeight, imagePath, zPosition),
		camera(GameCamera{}),
		parallaxFactor(parallaxFactor) {}
	Layer(const Layer&) = delete;
	Layer& operator=(const Layer&) = delete;
	Layer(Layer&& other) noexcept :
		background(std::move(other.background)),
		camera(std::move(other.camera)),
		parallaxFactor(other.parallaxFactor)
	{
		std::cout << "Layer MOVE\n";
	}
	Layer& operator=(Layer&&) = default;

	float getParallaxFactor() const
	{
		return parallaxFactor;
	}

	void render() const
	{
		background.render();
	}

	Camera2D getCamera() const
	{
		return camera.getCamera();
	}

	void setCameraPosition(float x, float y, float offsetX, float offsetY)
	{
		camera.setCameraPosition(x, y, 0, 0);
	}
};
