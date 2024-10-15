#pragma once

#include "Renderer.h"

class GameObject
{
public:
	RECT redrawRect, redrawPrevRect;
	Vector2 position;
	int width;
	int height;
	GameObject();
	GameObject(Vector2 position, int width, int height);
	void RedrawGameObject(bool isBallObject = false);
};