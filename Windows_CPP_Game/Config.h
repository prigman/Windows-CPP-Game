#pragma once

class SConfig
{
public:
	static const int BALL_SIZE = 4;
	static const int GLOBAL_SCALE = 3;
	
	static const int BORDER_X_OFFSET = 6;
	static const int BORDER_Y_OFFSET = 4;
	static const int BORDER_TILE_WIDTH = 4;
	static const int BORDER_TILE_HEIGHT = BORDER_TILE_WIDTH;
	static const int BORDER_LEFT_MARGIN = 2;
	static const int BORDER_RIGHT_MARGIN = 1;
	static const int BORDER_TOP_MARGIN = 1;

	static const int PLATFORM_ELLIPSE_SIZE = 7;
	static const int PLATFORM_BORDER_ROUND = 3;
	static const int PLATFORM_DEFAULT_X_POSITION = BORDER_X_OFFSET;
	static const int PLATFORM_DEFAULT_Y_POSITION = 185;

	static const int BRICK_HEIGHT = 7;
	static const int BRICK_WIDTH = 15;
	static const int BRICK_BORDER_ROUND = 2;


	static const int LEVEL_MAX_ROWS = 14;
	static const int LEVEL_MAX_BRICKS_IN_ROW = 12;

	static const int CELL_WIDTH = 16;
	static const int CELL_HEIGHT = 8;

	static const int LEVEL_X_OFFSET = 8;
	static const int LEVEL_Y_OFFSET = 6;

	static const int LEVEL_MAX_X_POSITION = LEVEL_X_OFFSET + CELL_WIDTH * LEVEL_MAX_BRICKS_IN_ROW;
	static const int LEVEL_MAX_Y_POSITION = 199 - SConfig::BALL_SIZE;

	static const int FRAMES_PER_SECOND = 20;
};