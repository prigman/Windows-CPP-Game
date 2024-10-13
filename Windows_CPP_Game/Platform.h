#pragma once

#include "StaticObject.h"
#include "EKeyType.h"

class Platform : public StaticObject
{
public:
	static const int PLATFORM_WIDTH = 28;
	static const int PLATFORM_HEIGHT = 7;

	static const int PLATFORM_DEFAULT_X_STEP = 3;

	
	static const int PLATFORM_DEFAULT_INNER_WIDTH = SConfig::PLATFORM_ELLIPSE_SIZE * 3;
	static const int PLATFORM_DEFAULT_WIDTH = PLATFORM_DEFAULT_INNER_WIDTH + SConfig::PLATFORM_ELLIPSE_SIZE;
	static const int PLATFORM_DEFAULT_HEIGHT = SConfig::PLATFORM_ELLIPSE_SIZE;

	int platformInnerWidth;
	int platformXStep;

	Platform() : StaticObject(Vector2(SConfig::PLATFORM_DEFAULT_X_POSITION, SConfig::PLATFORM_DEFAULT_Y_POSITION), PLATFORM_DEFAULT_WIDTH, PLATFORM_DEFAULT_HEIGHT), 
		platformInnerWidth(PLATFORM_DEFAULT_INNER_WIDTH),
		platformXStep(PLATFORM_DEFAULT_X_STEP)
	{}

	void MovePlatform(EKeyType keyType);
};