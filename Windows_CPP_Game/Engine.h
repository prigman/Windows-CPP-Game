#pragma once

#include "Border.h"
#include "Ball.h"
#include "Level.h"
#include "Platform.h"
#include "Brick.h"

class SGameEngine
{
private:
	void OnGameInitRedraw(HWND hWnd);
public:
	static const int TIMER_ID = WM_USER + 1;

	Ball objectBall;
	Brick objectBrick;
	Platform objectPlatform;
	Level objectLevel;
	Border objectBorder;

	//HWND hWnd;

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

	SGameEngine();
	void InitGame(HWND hWnd);
	int OnTimer();
	int OnKeyDown(EKeyType keyType);
};


extern SGameEngine Engine;