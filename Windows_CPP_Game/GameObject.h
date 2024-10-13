#pragma once

#include "Renderer.h"

class GameObject
{
public:
	RECT redrawRect, redrawPrevRect;
	Vector2 position;
	int width;
	int height;
	GameObject(): position(0,0), width(0), height(0), redrawRect{0, 0, 0, 0}, redrawPrevRect{0, 0, 0, 0} {}
	GameObject(Vector2 position, int width, int height) : position(position), width(width), height(height), redrawRect{0, 0, 0, 0}, redrawPrevRect{0, 0, 0, 0} {}
	
	void RedrawGameObject(bool isBallObject = false);
};