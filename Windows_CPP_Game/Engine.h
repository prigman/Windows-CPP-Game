#pragma once

#include <Windows.h>

#define BG_RGB_RED			50
#define BG_RGB_GREEN		64
#define BG_RGB_BLUE			117

#define BACKGROUND_COLOR    RGB(BG_RGB_RED, BG_RGB_GREEN, BG_RGB_BLUE)

enum EKeyType
{
	EKT_LEFT,
	EKT_RIGHT,
	EKT_SPACE
};

int OnKeyDown(EKeyType keyType);
void InitGame(HWND hWnd);
void DrawFrame(HDC hdc, RECT &paintArea);