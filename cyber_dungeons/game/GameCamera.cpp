#include "GameCamera.h"
#include <raylib.h>
#include <iostream>

void GameCamera::update()
{
}

void GameCamera::setCameraPosition(float x, float y)
{
	camera.target.x = x;
	camera.target.y = y;
	camera.offset.x = 600 / 2.0f;
	camera.offset.y = 600 / 2.0f;
}

Camera2D GameCamera::getCamera() const
{
	return camera;
}
