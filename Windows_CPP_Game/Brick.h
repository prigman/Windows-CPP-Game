#pragma once

#include "StaticObject.h"

class Brick : public StaticObject
{
private:
	static const int BRICK_MAX_FADE_STEP = 40;
public:

	int fadeStep;

	Brick() : StaticObject(Vector2(SConfig::LEVEL_X_OFFSET, 100), SConfig::BRICK_WIDTH, SConfig::BRICK_HEIGHT), fadeStep(0){}

	void Act();

};