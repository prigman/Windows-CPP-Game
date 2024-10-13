#pragma once

#define BG_RGB_RED		50
#define BG_RGB_GREEN	64
#define BG_RGB_BLUE		117

#define BACKGROUND_COLOR    RGB(BG_RGB_RED, BG_RGB_GREEN, BG_RGB_BLUE)

#include "Vector2.h"
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Config.h"
#include "ELetterType.h"
#include "EBrickType.h"

class Ball;
class Brick;
class Platform;
class Level;
class Border;

class SRenderer
{
private:
	void CreateEllipse(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale);
	void CreateRoundedRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, int borderRound, bool useGlobalScale);
	void CreateRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale);
	void CreateArc(HDC hDC, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, HPEN pen);
	void CreateLevelBorder(HDC hDC, Vector2 position, bool is_horizontal_line);
	void CreatePenAndBrush(unsigned char red, unsigned char green, unsigned char blue, HPEN &pen, HBRUSH &brush);
public:

	HWND hWnd;

	HPEN firstColorPen,
		secondColorPen,
		whiteColorPen,
		letterPen,
		backgroundPen,
		levelBorderFirstPen,
		levelBorderSecondPen,
		levelBorderThirdPen;

	HBRUSH firstColorBrush, 
		secondColorBrush,
		whiteColorBrush,
		backgroundBrush,
		levelBorderFirstBrush,
		levelBorderSecondBrush,
		levelBorderThirdBrush;


	SRenderer()
		:
		hWnd(nullptr),

		firstColorPen(nullptr),
		secondColorPen(nullptr),
		whiteColorPen(nullptr),
		letterPen(nullptr),
		backgroundPen(nullptr),
		levelBorderFirstPen(nullptr),
		levelBorderSecondPen(nullptr),
		levelBorderThirdPen(nullptr),

		backgroundBrush(nullptr),
		firstColorBrush(nullptr),
		secondColorBrush(nullptr),
		whiteColorBrush(nullptr),
		levelBorderFirstBrush(nullptr),
		levelBorderSecondBrush(nullptr),
		levelBorderThirdBrush(nullptr)

	{}
	void DrawFrame(HDC hDC, RECT &paintArea, Level *level, Platform *platform, Ball *ball, Brick *brick, Border *border);
	void SetPensAndBrushes();
	void CreateBrick(HDC hDC, Vector2 position, EBrickType brickColorType);
	void CreateAnimatedBrick(HDC hDC, Vector2 position, int brickWidth, EBrickType brickType, ELetterType letterType, int rotationStep);
	void CreateLevel(HDC hDC, const char level[SConfig::LEVEL_MAX_ROWS][SConfig::LEVEL_MAX_BRICKS_IN_ROW]);
	void CreatePlatform(HDC hDC, Vector2 platformPosition, int platformInnerWidth, RECT redrawPrevRect);
	void CreateBall(HDC hDC, RECT redrawRect, RECT redrawPrevRect);
	void CreateBounds(HDC hDC);
	void RedrawWindowArea(int left, int top, int right, int bottom, RECT &redrawRect, RECT &prevRedrawRect, bool isBallObject = false, BOOL clearBackground = FALSE) const;
};

extern SRenderer EngineRenderer;