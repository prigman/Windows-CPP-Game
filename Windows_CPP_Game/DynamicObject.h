#pragma once

#include "GameObject.h"

class DynamicObject : public GameObject {
public:
	double speed;
	double direction;
	DynamicObject(): GameObject(), speed(0.0), direction(0.0) {}
	DynamicObject(Vector2 position, int width, int height, double speed, double direction) : GameObject(position, width, height), speed(speed), direction(direction) {}
};