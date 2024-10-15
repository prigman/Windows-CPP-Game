#pragma once

#include "StaticObject.h"

// all bricks on a level
class Level : public StaticObject 
{
public:

	static char Level_01[SConfig::LEVEL_MAX_ROWS][SConfig::LEVEL_MAX_BRICKS_IN_ROW];

	Level();
	//void CheckLevelBrickHit(int &nextBallYPosition, double &direction) const;
};