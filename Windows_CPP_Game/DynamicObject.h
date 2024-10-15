#pragma once

#include "GameObject.h"

class DynamicObject : public GameObject {
public:
	double speed;
	double direction;
	DynamicObject();
	DynamicObject(Vector2 position, int width, int height, double speed, double direction);
};