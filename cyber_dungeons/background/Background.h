#pragma once

#include <raylib.h>
#include <cmath>
#include "GameCamera.h"

class Background
{
public:
	enum class ZPosition
	{
		NONE,
		SKY,
		FAR,
		MEDIUM,
		NEAR
	};
private:

	int screenWidth;
	int screenHeight;

	const char* imagePath;
	ZPosition zPosition;
	Texture2D texture;

public:
	GameCamera camera;
	Background(int screenWidth, int screenHeight, const char* imagePath, ZPosition zPosition);
	Background(const Background&) = delete;
	Background& operator=(const Background&) = delete;
	Background(Background&&) noexcept;
	Background& operator=(Background&&) noexcept;

	//Background(const Background& other);
	//Background(Background&& other) noexcept;
	~Background();

	// core
	void render() const;

	Camera2D getCamera() const;
};