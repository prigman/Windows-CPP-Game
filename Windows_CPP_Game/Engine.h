#pragma once

#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

constexpr char BG_RGB_RED = 50;
constexpr char BG_RGB_GREEN = 64;
constexpr char BG_RGB_BLUE = 117;

#define BACKGROUND_COLOR    RGB(BG_RGB_RED, BG_RGB_GREEN, BG_RGB_BLUE)

enum EKeyType
{
	EKT_LEFT,
	EKT_RIGHT,
	EKT_SPACE
};

enum EBrickType
{
	EBT_NONE,
	EBT_FIRST, // purple color
	EBT_SECOND // cyan color
};

enum ELetterType
{
	ELT_NONE,
	ELT_FIRST, // letter "O"
};

const int TIMER_ID = WM_USER + 1;

class SGameEngine
{
public:
	SGameEngine();

	static const int LEVEL_MAX_ROWS = 14;
	static const int LEVEL_MAX_BRICKS_IN_ROW = 12;

	void InitGame(HWND hWnd);
	void DrawFrame(HDC hdc, RECT& paintArea);
	int OnTimer();
	int OnKeyDown(EKeyType keyType);
private:
	HWND HWnd;

	HPEN FirstColorPen,
		SecondColorPen,
		WhiteColorPen,
		LetterPen,
		BackgroundPen,
		LevelBorderFirstPen,
		LevelBorderSecondPen,
		LevelBorderThirdPen;

	HBRUSH FirstColorBrush, 
		SecondColorBrush,
		WhiteColorBrush,
		BackgroundBrush,
		LevelBorderFirstBrush,
		LevelBorderSecondBrush,
		LevelBorderThirdBrush;

	RECT RedrawPlatformRect, RedrawPrevPlatformRect;
	RECT RedrawLevelRect, RedrawPrevLevelRect;
	RECT RedrawBallRect, RedrawPrevBallRect;
	RECT RedrawBordersRect, RedrawPrevBordersRect;

	/* SCALE OF THE GAME */
	static const int GLOBAL_SCALE = 3;

	/* BRICK DATA */
	static const int BRICK_WIDTH = 15;
	static const int BRICK_HEIGHT = 7;
	static const int BRICK_BORDER_ROUND = 2;

	/* CELL DATA */
	static const int CELL_WIDTH = 16;
	static const int CELL_HEIGHT = 8;

	/* BALL DATA */
	static const int BALL_DEFAULT_X_POSITION = 20;
	static const int BALL_DEFAULT_Y_POSITION = 170;
	static const int BALL_SIZE = 4;

	/* LEVEL DATA */

	static const int LEVEL_BORDER_TILE_WIDTH = 4;
	static const int LEVEL_BORDER_TILE_HEIGHT = LEVEL_BORDER_TILE_WIDTH;

	static const int LEVEL_BORDER_LEFT_MARGIN = 2;
	static const int LEVEL_BORDER_RIGHT_MARGIN = 1;
	static const int LEVEL_BORDER_TOP_MARGIN = 1;

	static const int LEVEL_BORDER_X_OFFSET = 6;
	static const int LEVEL_BORDER_Y_OFFSET = 4;

	static const int LEVEL_X_OFFSET = 8;
	static const int LEVEL_Y_OFFSET = 6;

	static const int LEVEL_MAX_X_POSITION = LEVEL_X_OFFSET + CELL_WIDTH * LEVEL_MAX_BRICKS_IN_ROW;
	static const int LEVEL_MAX_Y_POSITION = 199 - BALL_SIZE;

	/* PLATFORM DATA */
	static const int PLATFORM_BORDER_ROUND = 3;
	static const int PLATFORM_CIRCLE_SIZE = 7;
	static const int PLATFORM_DEFAULT_X_POSITION = LEVEL_BORDER_X_OFFSET;
	static const int PLATFORM_DEFAULT_Y_POSITION = 185;
	static const int PLATFORM_DEFAULT_INNER_WIDTH = PLATFORM_CIRCLE_SIZE * 3;
	static const int PLATFORM_DEFAULT_WIDTH = PLATFORM_DEFAULT_INNER_WIDTH + PLATFORM_CIRCLE_SIZE;
	static const int PLATFORM_DEFAULT_HEIGHT = PLATFORM_CIRCLE_SIZE;

	int PlatformInnerWidth;
	int PlatformXPosition;
	int PlatformXStep;

	int PlatformWidth;

	int BallXPosition;
	int BallYPosition;

	double BallSpeed, BallDirection;


	void CreateEllipse(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale);
	void CreateRoundedRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, int borderRound, bool useGlobalScale);
	void CreateRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale);
	void CreateArc(HDC hDC, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, HPEN pen);
	void CreatePlatform(HDC hDC, int posX, int posY);
	void CreateBall(HDC hDC);
	void CreateBrick(HDC hDC, int posX, int posY, EBrickType brickColorType);
	void CreateLevel(HDC hDC, char level[LEVEL_MAX_ROWS][LEVEL_MAX_BRICKS_IN_ROW]);
	void CreatePenAndBrush(unsigned char red, unsigned char green, unsigned char blue, HPEN& pen, HBRUSH& brush);
	void SetPensAndBrushes();
	void CreateAnimatedBrick(HDC hDC, int posX, int posY, EBrickType brickType, ELetterType letterType, int rotationStep);
	void RedrawWindowArea(int left, int top, int right, int bottom, RECT& redrawRect, RECT& prevRedrawRect, bool isBall = false, bool clearBackground = FALSE) const;
	void RedrawPlatform();
	void RedrawLevel();
	void RedrawBall();
	void RedrawBorders();
	void MoveBall();
	void CreateLevelBorder(HDC hDC,int posX, int posY, bool is_horizontal_line);
	void CreateBounds(HDC hDC);
	void CheckLevelBrickHit(int& nextBallYPosition);
};
