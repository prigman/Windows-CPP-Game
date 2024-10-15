#pragma once

#include "GameObject.h"

class StaticObject : public GameObject {
public:
	StaticObject();
	StaticObject(Vector2 position, int width, int height);
};