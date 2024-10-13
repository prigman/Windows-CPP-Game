#pragma once

#include "StaticObject.h"

// all bricks on a level
class Level : public StaticObject 
{
public:

	static char Level_01[SConfig::LEVEL_MAX_ROWS][SConfig::LEVEL_MAX_BRICKS_IN_ROW];

	Level() : StaticObject(Vector2(SConfig::LEVEL_X_OFFSET, SConfig::LEVEL_Y_OFFSET), SConfig::CELL_WIDTH, SConfig::CELL_HEIGHT){}

	//void CheckLevelBrickHit(int &nextBallYPosition, double &direction) const;
};