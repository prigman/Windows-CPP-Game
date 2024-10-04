#pragma once

#include <Windows.h>

constexpr int BG_RGB_RED = 50;
constexpr int BG_RGB_GREEN = 64;
constexpr int BG_RGB_BLUE = 117;

#define BACKGROUND_COLOR    RGB(BG_RGB_RED, BG_RGB_GREEN, BG_RGB_BLUE)

enum EKeyType
{
	EKT_LEFT,
	EKT_RIGHT,
	EKT_SPACE
};

const int TIMER_ID = WM_USER + 1;

int OnKeyDown(EKeyType keyType);
int OnTimer();
void InitGame(HWND hWnd);
void DrawFrame(HDC hdc, RECT &paintArea);