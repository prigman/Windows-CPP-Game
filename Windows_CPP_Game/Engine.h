#pragma once

#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define BG_RGB_RED		50
#define BG_RGB_GREEN	64
#define BG_RGB_BLUE		117

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

class Vector2
{
public:
	int x;
	int y;
	Vector2(): x(0), y(0) {}
	Vector2(int posX, int posY) : x(posX), y(posY) {}
};

class GameObject
{
public:
	RECT redrawRect, redrawPrevRect;
	Vector2 position;
	int width;
	int height;
	GameObject(): position(0,0), width(0), height(0), redrawRect{0, 0, 0, 0}, redrawPrevRect{0, 0, 0, 0} {}
	GameObject(Vector2 position, int width, int height) : position(position), width(width), height(height), redrawRect{0, 0, 0, 0}, redrawPrevRect{0, 0, 0, 0} {}
	
};

class DynamicObject : public GameObject {
public:
	double speed;
	double direction;
	DynamicObject(): GameObject(), speed(0.0), direction(0.0) {}
	DynamicObject(Vector2 position, int width, int height, double speed, double direction) : GameObject(position, width, height), speed(speed), direction(direction) {}
};

class StaticObject : public GameObject {
public:
	StaticObject(): GameObject(){}
	StaticObject(Vector2 position, int width, int height) : GameObject(position, width, height) {}
};

class Border : public StaticObject
{
public:
	static const int BORDER_TILE_WIDTH = 4;
	static const int BORDER_TILE_HEIGHT = BORDER_TILE_WIDTH;

	static const int BORDER_LEFT_MARGIN = 2;
	static const int BORDER_RIGHT_MARGIN = 1;
	static const int BORDER_TOP_MARGIN = 1;

	static const int BORDER_X_OFFSET = 6;
	static const int BORDER_Y_OFFSET = 4;

	Border() : StaticObject(Vector2(), BORDER_TILE_WIDTH, BORDER_TILE_HEIGHT){}

};

class Brick : public StaticObject
{
public:
	static const int BRICK_WIDTH = 15;
	static const int BRICK_HEIGHT = 7;
	static const int BRICK_BORDER_ROUND = 2;

	Brick() : StaticObject(Vector2(), BRICK_WIDTH, BRICK_HEIGHT){}

};

class Platform;
class Level;

class Ball : public DynamicObject
{
private:
	static const int BALL_DEFAULT_X_POSITION = 20;
	static const int BALL_DEFAULT_Y_POSITION = 170;
public:

	static const int BALL_SIZE = 4;

	//double BallDefaultSpeed; // 3.0
	//double BallDefaultDirection; // M_PI - M_PI_4

	Ball() : DynamicObject(Vector2(BALL_DEFAULT_X_POSITION, BALL_DEFAULT_Y_POSITION), BALL_SIZE, BALL_SIZE, 3.0, M_PI - M_PI_4) {}

	void MoveBall(Level *level, Platform *platform);

};

// all bricks on a level
class Level : public StaticObject 
{
public:
	static const int LEVEL_MAX_ROWS = 14;
	static const int LEVEL_MAX_BRICKS_IN_ROW = 12;

	static const int CELL_WIDTH = 16;
	static const int CELL_HEIGHT = 8;

	static const int LEVEL_X_OFFSET = 8;
	static const int LEVEL_Y_OFFSET = 6;

	static const int LEVEL_MAX_X_POSITION = LEVEL_X_OFFSET + CELL_WIDTH * LEVEL_MAX_BRICKS_IN_ROW;
	static const int LEVEL_MAX_Y_POSITION = 199 - Ball::BALL_SIZE;

	char Level_01[LEVEL_MAX_ROWS][LEVEL_MAX_BRICKS_IN_ROW] =
	{
		EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE,
		EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST,
		EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST,
		EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND,
		EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND,
		EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST,
		EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST, EBT_FIRST,
		EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND,
		EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND, EBT_SECOND,
		EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE,
		EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE,
		EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE,
		EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE,
		EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE, EBT_NONE,
	};

	Level() : StaticObject(Vector2(LEVEL_X_OFFSET, LEVEL_Y_OFFSET), CELL_WIDTH, CELL_HEIGHT){}

	void CheckLevelBrickHit(int &nextBallYPosition, double &direction) const;
};

class Platform : public StaticObject
{
public:
	static const int PLATFORM_WIDTH = 28;
	static const int PLATFORM_HEIGHT = 7;

	static const int PLATFORM_DEFAULT_X_STEP = 3;

	static const int PLATFORM_BORDER_ROUND = 3;
	static const int PLATFORM_CIRCLE_SIZE = 7;
	static const int PLATFORM_DEFAULT_X_POSITION = Border::BORDER_X_OFFSET;
	static const int PLATFORM_DEFAULT_Y_POSITION = 185;
	static const int PLATFORM_DEFAULT_INNER_WIDTH = PLATFORM_CIRCLE_SIZE * 3;
	static const int PLATFORM_DEFAULT_WIDTH = PLATFORM_DEFAULT_INNER_WIDTH + PLATFORM_CIRCLE_SIZE;
	static const int PLATFORM_DEFAULT_HEIGHT = PLATFORM_CIRCLE_SIZE;

	int platformInnerWidth;
	int platformXStep;

	Platform() : StaticObject(Vector2(PLATFORM_DEFAULT_X_POSITION, PLATFORM_DEFAULT_Y_POSITION), PLATFORM_DEFAULT_WIDTH, PLATFORM_DEFAULT_HEIGHT), 
		platformInnerWidth(PLATFORM_DEFAULT_INNER_WIDTH),
		platformXStep(PLATFORM_DEFAULT_X_STEP)
	{}

	void MovePlatform(EKeyType keyType, int globalScale);
};

class SGameEngine
{
public:

	static const int GLOBAL_SCALE = 3;
	static const int TIMER_ID = WM_USER + 1;

	Ball ObjectBall;
	Brick ObjectBrick;
	Platform ObjectPlatform;
	Level ObjectLevel;
	Border ObjectBorder;

	HWND HWnd;

	SGameEngine() : 
		HWnd(nullptr)
	{}

	void InitGame(HWND hWnd);
	int OnTimer();
	int OnKeyDown(EKeyType keyType);

};

class SRenderer
{
public:
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


	SRenderer()
		:
		FirstColorPen(nullptr),
		SecondColorPen(nullptr),
		WhiteColorPen(nullptr),
		LetterPen(nullptr),
		BackgroundPen(nullptr),
		LevelBorderFirstPen(nullptr),
		LevelBorderSecondPen(nullptr),
		LevelBorderThirdPen(nullptr),

		BackgroundBrush(nullptr),
		FirstColorBrush(nullptr),
		SecondColorBrush(nullptr),
		WhiteColorBrush(nullptr),
		LevelBorderFirstBrush(nullptr),
		LevelBorderSecondBrush(nullptr),
		LevelBorderThirdBrush(nullptr)

	{}
	void OnGameInitRenderer(SGameEngine *engine);
	void DrawFrame(HDC hdc, RECT &paintArea, SGameEngine *engine);
	void CreateBrick(HDC hDC, Vector2 position, EBrickType brickColorType);
	void RedrawGameObject(GameObject *gameObject) const;
	void SetPensAndBrushes();
	void CreateAnimatedBrick(HDC hDC, Vector2 position, Brick *brick, EBrickType brickType, ELetterType letterType, int rotationStep);

	void CreateLevel(HDC hDC, char level[Level::LEVEL_MAX_ROWS][Level::LEVEL_MAX_BRICKS_IN_ROW]);

private:

	void CreateEllipse(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale);
	void CreateRoundedRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, int borderRound, bool useGlobalScale);
	void CreateRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale);
	void CreateArc(HDC hDC, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, HPEN pen);
	void CreatePlatform(HDC hDC, Platform *platform);
	void CreateBall(HDC hDC, Ball *ball);
	void CreateLevelBorder(HDC hDC, Vector2 position, bool is_horizontal_line);
	void CreateBounds(HDC hDC);
	void RedrawWindowArea(int left, int top, int right, int bottom, RECT &redrawRect, RECT &prevRedrawRect, bool isBall = false, bool clearBackground = FALSE) const;
	void CreatePenAndBrush(unsigned char red, unsigned char green, unsigned char blue, HPEN &pen, HBRUSH &brush);
};

extern SGameEngine Engine;
extern SRenderer EngineRenderer;