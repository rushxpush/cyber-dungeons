#include "GameCamera.h"
#include <raylib.h>
#include <iostream>

void GameCamera::update()
{
}

void GameCamera::setCameraPosition(float x, float y, float offsetX, float offsetY)
{
	camera.target.x = x;
	camera.target.y = y;
	camera.offset.x = offsetX;
	camera.offset.y = offsetY;
}

Camera2D GameCamera::getCamera() const
{
	return camera;
}
