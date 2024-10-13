#pragma once

#include "StaticObject.h"

class Border : public StaticObject
{
public:

	Border() : StaticObject(Vector2(), SConfig::BORDER_TILE_WIDTH, SConfig::BORDER_TILE_HEIGHT){}
	
};