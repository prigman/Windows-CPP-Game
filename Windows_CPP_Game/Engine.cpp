#include "Engine.h"

#define _USE_MATH_DEFINES
#include <math.h>

HPEN FirstColorPen, 
SecondColorPen, 
WhiteColorPen, 
LetterPen;

HBRUSH FirstColorBrush, SecondColorBrush;

enum EBrickType
{
    EBT_NONE,
    EBT_FIRST, // letter "O"
    EBT_SECOND
};

enum ELetterType
{
    ELT_NONE,
    ELT_FIRST, // purple color
    ELT_SECOND // cyan color
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

static void CreateEllipse(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush)
{
    SelectObject(hDC, pen);
    if (brush != 0)
        SelectObject(hDC, brush);
    Ellipse(hDC, left * GLOBAL_SCALE, top * GLOBAL_SCALE, right * GLOBAL_SCALE, bottom * GLOBAL_SCALE);
}

static void CreateCustomEllipse(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush)
{
    SelectObject(hDC, pen);
    if (brush != 0)
        SelectObject(hDC, brush);
    Ellipse(hDC, left, top, right, bottom);
}

static void CreateRoundedRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush)
{
    SelectObject(hDC, pen);
    if (brush != 0)
        SelectObject(hDC, brush);
    RoundRect(hDC, left * GLOBAL_SCALE, top * GLOBAL_SCALE, right * GLOBAL_SCALE, bottom * GLOBAL_SCALE, PLATFORM_BORDER_ROUND, PLATFORM_BORDER_ROUND);
}

static void CreateRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush)
{
    SelectObject(hDC, pen);
    if (brush != 0)
        SelectObject(hDC, brush);
    Rectangle(hDC, left * GLOBAL_SCALE, top * GLOBAL_SCALE, right * GLOBAL_SCALE, bottom * GLOBAL_SCALE);
}

static void CreateCustomRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush)
{
    SelectObject(hDC, pen);
    if (brush != 0)
        SelectObject(hDC, brush);
    Rectangle(hDC, left, top, right, bottom);
}

static void CreateArc(HDC hDC, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, HPEN pen)
{
    SelectObject(hDC, pen);
    Arc(hDC, x1 * GLOBAL_SCALE, y1 * GLOBAL_SCALE, x2 * GLOBAL_SCALE, y2 * GLOBAL_SCALE, x3 * GLOBAL_SCALE, y3 * GLOBAL_SCALE, x4 * GLOBAL_SCALE, y4 * GLOBAL_SCALE);
}

static void CreatePlatform(HDC hDC, int posX, int posY)
{
    int platformXOffset = 4;
    int platformYOffset = 1;

    int platformWidth = 20;
    int platformHeight = 5;

    CreateEllipse(hDC, posX, posY, posX + PLATFORM_CIRCLE_SIZE, posY + PLATFORM_CIRCLE_SIZE, FirstColorPen, FirstColorBrush);
    CreateEllipse(hDC, posX + PlatformInnerWidth, posY, posX + PLATFORM_CIRCLE_SIZE + PlatformInnerWidth, posY + PLATFORM_CIRCLE_SIZE, FirstColorPen, FirstColorBrush);

    CreateRoundedRect(hDC, posX + platformXOffset, posY + platformYOffset, posX + platformXOffset + platformWidth, posY + platformYOffset + platformHeight, SecondColorPen, SecondColorBrush);

    // draw highlight on the ellipse
    CreateArc(hDC, posX + 1, posY + 1, posX + PLATFORM_CIRCLE_SIZE - 1, posY + PLATFORM_CIRCLE_SIZE - 1, posX + 1 + 1, posY + 1, posX + 1, posY + 1 + 2, WhiteColorPen);
}

static void CreateBrick(HDC hDC, int posX, int posY, EBrickType brickColorType) // create brick based on its color type
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

    CreateRoundedRect(hDC, posX, posY, posX + BRICK_WIDTH, posY + BRICK_HEIGHT, pen, brush);
}

static void CreateLevel(HDC hDC, char level[LEVEL_MAX_ROWS][LEVEL_MAX_BRICKS_IN_ROW]) // draw bricks in rows
{
    for (int i = 0; i < LEVEL_MAX_ROWS; i++)
        for (int j = 0; j < LEVEL_MAX_BRICKS_IN_ROW; j++)
            CreateBrick(hDC, LEVEL_X_OFFSET + j * CELL_WIDTH, LEVEL_Y_OFFSET + i * CELL_HEIGHT, (EBrickType)level[i][j]);
    CreatePlatform(hDC, 50, 100);
}

static void CreatePenAndBrush(unsigned char red, unsigned char green, unsigned char blue, HPEN &pen, HBRUSH &brush)
{
    pen = CreatePen(PS_SOLID, 0, RGB(red, green, blue));
    brush = CreateSolidBrush(RGB(red, green, blue));
}

static void SetPensAndBrushes()
{
    WhiteColorPen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
    LetterPen = CreatePen(PS_SOLID, GLOBAL_SCALE, RGB(255, 255, 255));
    CreatePenAndBrush(255, 128, 255, FirstColorPen, FirstColorBrush); // purple color
    CreatePenAndBrush(128, 255, 255, SecondColorPen, SecondColorBrush); // cyan color
}

static void CreateAnimatedBrick(HDC hDC, int posX, int posY, EBrickType brickType, ELetterType letterType, int rotationStep)
{
    posX *= GLOBAL_SCALE;

    double rotationAngle; // converting step to rotation angle
    double offset = 0.0;

    int brickHalfHeight = BRICK_HEIGHT / 2 * GLOBAL_SCALE;
    int brickBackPartOffset = 0;

    HPEN frontColorPen{}, backColorPen{};
    HBRUSH frontColorBrush{}, backColorBrush{};
    
    XFORM xForm{}, previousXForm{};
    GetWorldTransform(hDC, &previousXForm); // save the current world transform 

    rotationStep %= 16;

    if (rotationStep < 8)
        rotationAngle = 2.0 * M_PI / 16.0 * (double) rotationStep;
    else
        rotationAngle = 2.0 * M_PI / 16.0 * (double)(8L - (long long)rotationStep);

    if (rotationStep > 4 && rotationStep <= 12)
    {
        if (brickType == EBT_SECOND)
        {
            frontColorPen = FirstColorPen;
            frontColorBrush = FirstColorBrush;

            backColorPen = SecondColorPen;
            backColorBrush = SecondColorBrush;
        }
        else
        {
            frontColorPen = SecondColorPen;
            frontColorBrush = SecondColorBrush;

            backColorPen = FirstColorPen;
            backColorBrush = FirstColorBrush;
        }
    }
    else
    {
        if (brickType == EBT_FIRST)
        {
            frontColorPen = FirstColorPen;
            frontColorBrush = FirstColorBrush;

            backColorPen = SecondColorPen;
            backColorBrush = SecondColorBrush;
        }
        else
        {
            frontColorPen = SecondColorPen;
            frontColorBrush = SecondColorBrush;

            backColorPen = FirstColorPen;
            backColorBrush = FirstColorBrush;
        }
    }

    if (rotationStep == 4 || rotationStep == 12)
    {
        // background output
        CreateCustomRect(hDC, posX, posY + brickHalfHeight - GLOBAL_SCALE, posX + BRICK_WIDTH * GLOBAL_SCALE, posY + brickHalfHeight, backColorPen, backColorBrush); // 0, 0 because of xForm's eDx, eDy
        // front side output
        CreateCustomRect(hDC, posX, posY + brickHalfHeight, posX + BRICK_WIDTH * GLOBAL_SCALE, posY + brickHalfHeight + GLOBAL_SCALE - 1, frontColorPen, frontColorBrush); // 0, 0 because of xForm's eDx, eDy
    }
    else
    {
     //rotation matrix of the brick
        xForm.eM11 = 1.0f;
        xForm.eM12 = 0.0f;
        xForm.eM21 = 0.0f;
        xForm.eM22 = (float) cos(rotationAngle);
        xForm.eDx  = (float) posX; // coord x
        xForm.eDy  = (float) posY + (float) brickHalfHeight; // coord y

        SetWorldTransform(hDC, &xForm); // change world transform to the new value

   
        offset = 3.0 * (1.0 - fabs(xForm.eM22)) * (double)GLOBAL_SCALE;
        brickBackPartOffset = (int)round(offset);

        //background output
        CreateCustomRect(hDC, 0, -brickHalfHeight - brickBackPartOffset, BRICK_WIDTH * GLOBAL_SCALE, brickHalfHeight - brickBackPartOffset, backColorPen, backColorBrush); // 0, 0 because of xForm's eDx, eDy


        // front side output
        CreateCustomRect(hDC, 0, -brickHalfHeight, BRICK_WIDTH * GLOBAL_SCALE, brickHalfHeight, frontColorPen, frontColorBrush); // 0, 0 because of xForm's eDx, eDy

        if (rotationStep > 4 && rotationStep <= 12)
        {
            if (letterType == ELT_FIRST)
                CreateCustomEllipse(hDC, 0 + 5 * GLOBAL_SCALE, (-5 * GLOBAL_SCALE) / 2, 0 + 10 * GLOBAL_SCALE, 5 * GLOBAL_SCALE / 2, LetterPen, NULL);
            // else
        }

        SetWorldTransform(hDC, &previousXForm); // change world transform to the old value
    }
}

void InitGame()
{
    SetPensAndBrushes();
}

void DrawFrame(HDC hDC) // draw new information in window
{
    /*
    * Example of drawing a rectangle:
    * 
    // CreateRect(hDC, 20, 50, 20 + BRICK_WIDTH, 50 + BRICK_HEIGHT);
    * 
    * left, right = x coord | top, bottom = y coord
    * x, y can be modified by the width and height of the shape
    */

    //CreateLevel(hDC, Level_01); // creating the prepared level with bricks and platform

    SetGraphicsMode(hDC, GM_ADVANCED); // using for SetWorldTransform()
    
    for (int i = 0; i < 16; i++)
    {
        CreateAnimatedBrick(hDC, 20 + i * CELL_WIDTH, 100, EBT_SECOND, ELT_FIRST, i);
        CreateAnimatedBrick(hDC, 20 + i * CELL_WIDTH, 130, EBT_FIRST, ELT_FIRST, i);
    }
}