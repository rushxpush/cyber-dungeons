#pragma once

#include <raylib.h>

class GameCamera
{
private:
	Camera2D camera;

public:
	GameCamera()
	{
		camera = {};
		camera.offset.x = 0;
		camera.offset.y = 0;
		camera.target.x = 0;
		camera.target.y = 0;
		camera.rotation = 0.0f;
		camera.zoom = 1.8f;
	}

	GameCamera(GameCamera&&) noexcept = default;
	GameCamera& operator=(GameCamera&&) noexcept = default;

	void update();

	Camera2D getCamera() const;

	void setCameraPosition(float x, float y, float offsetX, float offsetY);
};