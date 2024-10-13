#pragma once

#include "StaticObject.h"

class Brick : public StaticObject
{
public:
	
	Brick() : StaticObject(Vector2(), SConfig::BRICK_WIDTH, SConfig::BRICK_HEIGHT){}

};