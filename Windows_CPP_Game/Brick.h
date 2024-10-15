#pragma once

#include "StaticObject.h"

class Brick : public StaticObject
{
private:
	static const int BRICK_MAX_FADE_STEP = 40;
public:

	int fadeStep;

	Brick();

	void Act();

};