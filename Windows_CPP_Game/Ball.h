#pragma once

#include "DynamicObject.h"

class Ball : public DynamicObject
{
private:
	static const int BALL_DEFAULT_X_POSITION = 20;
	static const int BALL_DEFAULT_Y_POSITION = 170;

	void CheckLevelBrickHit(const char level[SConfig::LEVEL_MAX_ROWS][SConfig::LEVEL_MAX_BRICKS_IN_ROW], int &nextBallYPosition, double &direction) const;
public:

	//static const int BALL_SIZE = 4;

	//double BallDefaultSpeed; // 3.0
	//double BallDefaultDirection; // M_PI - M_PI_4

	Ball();

	void MoveBall(const char level[SConfig::LEVEL_MAX_ROWS][SConfig::LEVEL_MAX_BRICKS_IN_ROW], Vector2 platformPosition, int platformWidth);
	
};