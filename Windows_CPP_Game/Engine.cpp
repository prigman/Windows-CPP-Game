#include "Engine.h"

HPEN brickPurplePen, brickCyanPen;
HBRUSH brickPurpleBrush, brickCyanBrush;


enum EBrickColorType
{
    EBCT_NONE,
    EBCT_PURPLE,
    EBCT_CYAN
};

const int GLOBAL_SCALE = 3;

const int BRICK_WIDTH = 15;
const int BRICK_HEIGHT = 7;
const int BRICK_BORDER_ROUND = 6;

const int CELL_WIDTH = 16;
const int CELL_HEIGHT = 8;

const int LEVEL_X_OFFSET = 8;
const int LEVEL_Y_OFFSET = 6;

const int LEVEL_MAX_ROWS = 14;
const int LEVEL_MAX_BRICKS_IN_ROW = 12;

char Level_01[LEVEL_MAX_ROWS][LEVEL_MAX_BRICKS_IN_ROW] =
{
    EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE,
    EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE,
    EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE,
    EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN,
    EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN,
    EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE,
    EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE, EBCT_PURPLE,
    EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN,
    EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN, EBCT_CYAN,
    EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE,
    EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE,
    EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE,
    EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE,
    EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE, EBCT_NONE,
};

static void CreateBrick(HDC hdc, int posX, int posY, EBrickColorType brickColorType) // create brick based on its color type
{
    HPEN pen;
    HBRUSH brush;

    switch (brickColorType)
    {
    case EBCT_NONE:
    {
        return;
    }
    case EBCT_PURPLE:
    {
        pen = brickPurplePen;
        brush = brickPurpleBrush;
        break;
    }
    case EBCT_CYAN:
    {
        pen = brickCyanPen;
        brush = brickCyanBrush;
        break;
    }
    default:
    {
        return;
    }
    }

    SelectObject(hdc, pen);
    SelectObject(hdc, brush);

    RoundRect(hdc, posX * GLOBAL_SCALE, posY * GLOBAL_SCALE, (posX + BRICK_WIDTH) * GLOBAL_SCALE, (posY + BRICK_HEIGHT) * GLOBAL_SCALE, BRICK_BORDER_ROUND, BRICK_BORDER_ROUND);
}

static void CreateLevel(HDC hdc, char level[LEVEL_MAX_ROWS][LEVEL_MAX_BRICKS_IN_ROW]) // draw bricks in rows
{
    for (int i = 0; i < LEVEL_MAX_ROWS; i++)
        for (int j = 0; j < LEVEL_MAX_BRICKS_IN_ROW; j++)
            CreateBrick(hdc, LEVEL_X_OFFSET + j * CELL_WIDTH, LEVEL_Y_OFFSET + i * CELL_HEIGHT, (EBrickColorType)level[i][j]);
}

void InitGame()
{
    brickPurplePen = CreatePen(PS_SOLID, 0, RGB(255, 128, 255)); // border
    brickPurpleBrush = CreateSolidBrush(RGB(255, 128, 255)); // solid color

    brickCyanPen = CreatePen(PS_SOLID, 0, RGB(128, 255, 255));
    brickCyanBrush = CreateSolidBrush(RGB(128, 255, 255));
}

void DrawFrame(HDC hdc) // draw new information in window
{
    //CreateLevel(hdc, Level_01);
    int x = 50;
    int y = 100;
    int circleSize = 7;
    int innerWidth = 21;

    int xOffset = 4;

    SelectObject(hdc, brickPurplePen);
    SelectObject(hdc, brickPurpleBrush);
    Ellipse(hdc, x * GLOBAL_SCALE, y * GLOBAL_SCALE, (x + circleSize) * GLOBAL_SCALE, (y + circleSize) * GLOBAL_SCALE);
    Ellipse(hdc, (x + innerWidth) * GLOBAL_SCALE, y * GLOBAL_SCALE, (x + circleSize + innerWidth) * GLOBAL_SCALE, (y + circleSize) * GLOBAL_SCALE);
    SelectObject(hdc, brickCyanPen);
    SelectObject(hdc, brickCyanBrush);
    RoundRect(hdc, (x + 4) * GLOBAL_SCALE, (y + 1) * GLOBAL_SCALE, (x + 4 + 20) * GLOBAL_SCALE, (y + 1 + 5) * GLOBAL_SCALE, BRICK_BORDER_ROUND, BRICK_BORDER_ROUND);
}