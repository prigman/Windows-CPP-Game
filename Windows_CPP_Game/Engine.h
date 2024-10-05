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
		BackgroundPen;

	HBRUSH FirstColorBrush, 
		SecondColorBrush,
		WhiteColorBrush,
		BackgroundBrush;

	RECT RedrawPlatformRect, RedrawPrevPlatformRect;
	RECT RedrawLevelRect, RedrawPrevLevelRect;
	RECT RedrawBallRect, RedrawPrevBallRect;

	/* SCALE OF THE GAME */
	static const int GLOBAL_SCALE = 3;

	/* BRICK DATA */
	static const int BRICK_WIDTH = 15;
	static const int BRICK_HEIGHT = 7;
	static const int BRICK_BORDER_ROUND = 2;

	/* PLATFORM DATA */
	static const int PLATFORM_BORDER_ROUND = 3;
	static const int PLATFORM_CIRCLE_SIZE = 7;
	static const int PLATFORM_DEFAULT_X_POSITION = 0;
	static const int PLATFORM_DEFAULT_Y_POSITION = 185;
	static const int PLATFORM_DEFAULT_INNER_WIDTH = 21;
	static const int PLATFORM_DEFAULT_WIDTH = 28;
	static const int PLATFORM_DEFAULT_HEIGHT = 7;

	int PlatformInnerWidth;
	int PlatformXPosition;
	int PlatformXStep;

	int PlatformWidth;

	/* BALL DATA */
	static const int BALL_DEFAULT_X_POSITION = 20;
	static const int BALL_DEFAULT_Y_POSITION = 170;
	static const int BALL_SIZE = 4;

	int BallXPosition;
	int BallYPosition;

	double BallSpeed, BallDirection;

	/* CELL DATA */
	static const int CELL_WIDTH = 16;
	static const int CELL_HEIGHT = 8;

	/* LEVEL DATA */
	static const int LEVEL_X_OFFSET = 8;
	static const int LEVEL_Y_OFFSET = 6;

	static const int LEVEL_MAX_X_POSITION = LEVEL_X_OFFSET + CELL_WIDTH * LEVEL_MAX_ROWS - BALL_SIZE;
	static const int LEVEL_MAX_Y_POSITION = 199 - BALL_SIZE;

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
	void MoveBall();
};
