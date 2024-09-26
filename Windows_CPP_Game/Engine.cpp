#include "Engine.h"

HPEN FirstColorPen, SecondColorPen;
HBRUSH FirstColorBrush, SecondColorBrush;

enum EBrickType
{
    EBT_NONE,
    EBT_FIRST,
    EBT_SECOND
};

const int GLOBAL_SCALE = 3;

const int BRICK_WIDTH = 15;
const int BRICK_HEIGHT = 7;
const int BRICK_BORDER_ROUND = 2 * GLOBAL_SCALE;

const int PLATFORM_BORDER_ROUND = 3 * GLOBAL_SCALE;
const int PLATFORM_CIRCLE_SIZE = 7;
int PlatformInnerWidth = 21;

const int CELL_WIDTH = 16;
const int CELL_HEIGHT = 8;

const int LEVEL_X_OFFSET = 8;
const int LEVEL_Y_OFFSET = 6;

const int LEVEL_MAX_ROWS = 14;
const int LEVEL_MAX_BRICKS_IN_ROW = 12;

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

static void CreateEllipse(HDC hdc, int left, int top, int right, int bottom, HPEN pen = FirstColorPen, HBRUSH brush = FirstColorBrush)
{
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    Ellipse(hdc, left * GLOBAL_SCALE, top * GLOBAL_SCALE, right * GLOBAL_SCALE, bottom * GLOBAL_SCALE);
}

static void CreateRoundedRect(HDC hdc, int left, int top, int right, int bottom, HPEN pen = SecondColorPen, HBRUSH brush = SecondColorBrush)
{
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    RoundRect(hdc, left * GLOBAL_SCALE, top * GLOBAL_SCALE, right * GLOBAL_SCALE, bottom * GLOBAL_SCALE, PLATFORM_BORDER_ROUND, PLATFORM_BORDER_ROUND);
}

static void CreatePlatform(HDC hdc, int posX, int posY)
{
    int platformXOffset = 4;
    int platformYOffset = 1;

    int platformWidth = 20;
    int platformHeight = 5;

    CreateEllipse(hdc, posX, posY, posX + PLATFORM_CIRCLE_SIZE, posY + PLATFORM_CIRCLE_SIZE);
    CreateEllipse(hdc, posX + PlatformInnerWidth, posY, posX + PLATFORM_CIRCLE_SIZE + PlatformInnerWidth, posY + PLATFORM_CIRCLE_SIZE);

    CreateRoundedRect(hdc, posX + platformXOffset, posY + platformYOffset, posX + platformXOffset + platformWidth, posY + platformYOffset + platformHeight);
}

static void CreateBrick(HDC hdc, int posX, int posY, EBrickType brickColorType) // create brick based on its color type
{
    HPEN pen;
    HBRUSH brush;

    switch (brickColorType)
    {
    case EBT_NONE:
    {
        return;
    }
    case EBT_FIRST:
    {
        pen = FirstColorPen;
        brush = FirstColorBrush;
        break;
    }
    case EBT_SECOND:
    {
        pen = SecondColorPen;
        brush = SecondColorBrush;
        break;
    }
    default:
    {
        return;
    }
    }

    CreateRoundedRect(hdc, posX, posY, posX + BRICK_WIDTH, posY + BRICK_HEIGHT, pen, brush);
}

static void CreateLevel(HDC hdc, char level[LEVEL_MAX_ROWS][LEVEL_MAX_BRICKS_IN_ROW]) // draw bricks in rows
{
    for (int i = 0; i < LEVEL_MAX_ROWS; i++)
        for (int j = 0; j < LEVEL_MAX_BRICKS_IN_ROW; j++)
            CreateBrick(hdc, LEVEL_X_OFFSET + j * CELL_WIDTH, LEVEL_Y_OFFSET + i * CELL_HEIGHT, (EBrickType)level[i][j]);
    CreatePlatform(hdc, 50, 100);
}

static void CreatePenAndBrush(unsigned char red, unsigned char green, unsigned char blue, HPEN &pen, HBRUSH &brush)
{
    pen = CreatePen(PS_SOLID, 0, RGB(red, green, blue));
    brush = CreateSolidBrush(RGB(red, green, blue));
}

static void SetPensAndBrushes()
{
    CreatePenAndBrush(255, 128, 255, FirstColorPen, FirstColorBrush); // purple color
    CreatePenAndBrush(128, 255, 255, SecondColorPen, SecondColorBrush); // cyan color
}

void InitGame()
{
    SetPensAndBrushes();
}

void DrawFrame(HDC hdc) // draw new information in window
{
    CreateLevel(hdc, Level_01);
}