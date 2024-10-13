#pragma once

#include "GameObject.h"

class StaticObject : public GameObject {
public:
	StaticObject(): GameObject(){}
	StaticObject(Vector2 position, int width, int height) : GameObject(position, width, height) {}
};