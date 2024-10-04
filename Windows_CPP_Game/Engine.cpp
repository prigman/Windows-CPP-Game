#include "Engine.h"

#define _USE_MATH_DEFINES
#include <math.h>

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

/* SCALE OF THE GAME */
const int GLOBAL_SCALE = 3;

/* BRICK DATA */
const int BRICK_WIDTH = 15;
const int BRICK_HEIGHT = 7;
const int BRICK_BORDER_ROUND = 2;

/* PLATFORM DATA */
const int PLATFORM_BORDER_ROUND = 3;
const int PLATFORM_CIRCLE_SIZE = 7;
const int PLATFORM_DEFAULT_X_POSITION = 0;
const int PLATFORM_DEFAULT_Y_POSITION = 185;
const int PLATFORM_DEFAULT_INNER_WIDTH = 21;
const int PLATFORM_DEFAULT_WIDTH = 28;
const int PLATFORM_DEFAULT_HEIGHT = 7;

int PlatformInnerWidth = PLATFORM_DEFAULT_INNER_WIDTH;
int PlatformXPosition = PLATFORM_DEFAULT_X_POSITION;
int PlatformXStep = GLOBAL_SCALE * 2;

int PlatformWidth = PLATFORM_DEFAULT_WIDTH;

/* BALL DATA */
const int BALL_DEFAULT_X_POSITION = 20;
const int BALL_DEFAULT_Y_POSITION = 170;
const int BALL_SIZE = 4;

int BallXPosition = BALL_DEFAULT_X_POSITION;
int BallYPosition = BALL_DEFAULT_Y_POSITION;

double BallSpeed = 3.0, BallDirection = M_PI - M_PI_4;

/* CELL DATA */
const int CELL_WIDTH = 16;
const int CELL_HEIGHT = 8;

/* LEVEL DATA */
const int LEVEL_X_OFFSET = 8;
const int LEVEL_Y_OFFSET = 6;

const int LEVEL_MAX_ROWS = 14;
const int LEVEL_MAX_BRICKS_IN_ROW = 12;
const int LEVEL_MAX_X_POSITION = LEVEL_X_OFFSET + CELL_WIDTH * LEVEL_MAX_ROWS - BALL_SIZE;
const int LEVEL_MAX_Y_POSITION = 199 - BALL_SIZE;

/* FIRST LEVEL, BRICKS POSITION */

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

static void CreateEllipse(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale)
{
    if (useGlobalScale)
    {
        left *= GLOBAL_SCALE;
        top *= GLOBAL_SCALE;
        right *= GLOBAL_SCALE;
        bottom *= GLOBAL_SCALE;
    }
    SelectObject(hDC, pen);
    if (brush != 0)
        SelectObject(hDC, brush);
    Ellipse(hDC, left, top, right, bottom);
}

static void CreateRoundedRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, int borderRound, bool useGlobalScale)
{
    if (useGlobalScale)
    {
        left *= GLOBAL_SCALE;
        top *= GLOBAL_SCALE;
        right *= GLOBAL_SCALE;
        bottom *= GLOBAL_SCALE;
    }
    SelectObject(hDC, pen);
    if (brush != 0)
        SelectObject(hDC, brush);
    RoundRect(hDC, left, top, right, bottom, borderRound, borderRound);
}

static void CreateRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale)
{
    /*
    * Example of drawing a rectangle:
    * 
    // CreateRect(hDC, 20, 50, 20 + BRICK_WIDTH, 50 + BRICK_HEIGHT, FirstColorPen, FirstColorBrush, true);
    * 
    * left, right = x coord | top, bottom = y coord
    * x, y can be modified by the width and height of the shape
    */
    if (useGlobalScale)
    {
        left *= GLOBAL_SCALE;
        top *= GLOBAL_SCALE;
        right *= GLOBAL_SCALE;
        bottom *= GLOBAL_SCALE;
    }
    SelectObject(hDC, pen);
    if (brush != 0) // if not brush then draw only a border of the shape
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
    // draw a background before creating a platform
    CreateRect(hDC, RedrawPrevPlatformRect.left, RedrawPrevPlatformRect.top, RedrawPrevPlatformRect.right, RedrawPrevPlatformRect.bottom, BackgroundPen, BackgroundBrush, false);

    int platformXOffset = 4;
    int platformYOffset = 1;

    int platformWidth = 20;
    int platformHeight = 5;

    CreateEllipse(hDC, posX, posY, posX + PLATFORM_CIRCLE_SIZE, posY + PLATFORM_CIRCLE_SIZE, FirstColorPen, FirstColorBrush, true);
    CreateEllipse(hDC, posX + PlatformInnerWidth, posY, posX + PLATFORM_CIRCLE_SIZE + PlatformInnerWidth, posY + PLATFORM_CIRCLE_SIZE, FirstColorPen, FirstColorBrush, true);

    CreateRoundedRect(hDC, posX + platformXOffset, posY + platformYOffset, posX + platformXOffset + platformWidth, posY + platformYOffset + platformHeight, SecondColorPen, SecondColorBrush, PLATFORM_BORDER_ROUND, true);

    // draw highlight on the ellipse
    CreateArc(hDC, posX + 1, posY + 1, posX + PLATFORM_CIRCLE_SIZE - 1, posY + PLATFORM_CIRCLE_SIZE - 1, posX + 1 + 1, posY + 1, posX + 1, posY + 1 + 2, WhiteColorPen);
}

static void CreateBall(HDC hDC)
{
    // draw a background before creating a platform
    CreateEllipse(hDC, RedrawPrevBallRect.left, RedrawPrevBallRect.top, RedrawPrevBallRect.right, RedrawPrevBallRect.bottom, BackgroundPen, BackgroundBrush, false);

    CreateEllipse(hDC, RedrawBallRect.left, RedrawBallRect.top, RedrawBallRect.right, RedrawBallRect.bottom, WhiteColorPen, WhiteColorBrush, false);
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

    CreateRoundedRect(hDC, posX, posY, posX + BRICK_WIDTH, posY + BRICK_HEIGHT, pen, brush, BRICK_BORDER_ROUND, true);
}

static void CreateLevel(HDC hDC, char level[LEVEL_MAX_ROWS][LEVEL_MAX_BRICKS_IN_ROW]) // draw bricks in rows
{
    for (int i = 0; i < LEVEL_MAX_ROWS; i++)
        for (int j = 0; j < LEVEL_MAX_BRICKS_IN_ROW; j++)
            CreateBrick(hDC, LEVEL_X_OFFSET + j * CELL_WIDTH, LEVEL_Y_OFFSET + i * CELL_HEIGHT, (EBrickType)level[i][j]);
}

static void CreatePenAndBrush(unsigned char red, unsigned char green, unsigned char blue, HPEN &pen, HBRUSH &brush)
{
    pen = CreatePen(PS_SOLID, 0, RGB(red, green, blue));
    brush = CreateSolidBrush(RGB(red, green, blue));
}

static void SetPensAndBrushes()
{
    //WhiteColorPen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
    CreatePenAndBrush(255, 255, 255, WhiteColorPen, WhiteColorBrush);
    LetterPen = CreatePen(PS_SOLID, GLOBAL_SCALE, RGB(255, 255, 255));
    CreatePenAndBrush(BG_RGB_RED, BG_RGB_GREEN, BG_RGB_BLUE, BackgroundPen, BackgroundBrush); // backround color
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

    //rotationStep %= 16;

    if (rotationStep < 8)
        rotationAngle = 2.0 * M_PI / 16.0 * (double) rotationStep;
    else
        rotationAngle = 2.0 * M_PI / 16.0 * (double)(8L - (long long)rotationStep);

    if (rotationStep > 4 && rotationStep <= 12)
    {
        switch (brickType)
        {
        case EBT_SECOND:
        {
            frontColorPen = FirstColorPen;
            frontColorBrush = FirstColorBrush;

            backColorPen = SecondColorPen;
            backColorBrush = SecondColorBrush;
            break;
        }
        default:
        {
            frontColorPen = SecondColorPen;
            frontColorBrush = SecondColorBrush;

            backColorPen = FirstColorPen;
            backColorBrush = FirstColorBrush;
            break;
        }
        }
    }
    else
    {
        switch (brickType)
        {
        case EBT_FIRST:
        {
            frontColorPen = FirstColorPen;
            frontColorBrush = FirstColorBrush;

            backColorPen = SecondColorPen;
            backColorBrush = SecondColorBrush;
            break;
        }
        default:
        {
            frontColorPen = SecondColorPen;
            frontColorBrush = SecondColorBrush;

            backColorPen = FirstColorPen;
            backColorBrush = FirstColorBrush;
            break;
        }
        }
    }

    if (rotationStep == 4 || rotationStep == 12)
    {
        // background output
        CreateRect(hDC, posX, posY + brickHalfHeight - GLOBAL_SCALE, posX + BRICK_WIDTH * GLOBAL_SCALE, posY + brickHalfHeight, backColorPen, backColorBrush, false); // 0, 0 because of xForm's eDx, eDy
        // front side output
        CreateRect(hDC, posX, posY + brickHalfHeight, posX + BRICK_WIDTH * GLOBAL_SCALE, posY + brickHalfHeight + GLOBAL_SCALE - 1, frontColorPen, frontColorBrush, false); // 0, 0 because of xForm's eDx, eDy
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
        CreateRect(hDC, 0, -brickHalfHeight - brickBackPartOffset, BRICK_WIDTH * GLOBAL_SCALE, brickHalfHeight - brickBackPartOffset, backColorPen, backColorBrush, false); // 0, 0 because of xForm's eDx, eDy


        // front side output
        CreateRect(hDC, 0, -brickHalfHeight, BRICK_WIDTH * GLOBAL_SCALE, brickHalfHeight, frontColorPen, frontColorBrush, false); // 0, 0 because of xForm's eDx, eDy

        if (rotationStep > 4 && rotationStep <= 12)
        {
            if (letterType == ELT_FIRST)
                CreateEllipse(hDC, 0 + 5 * GLOBAL_SCALE, (-5 * GLOBAL_SCALE) / 2, 0 + 10 * GLOBAL_SCALE, 5 * GLOBAL_SCALE / 2, LetterPen, NULL, false);
            // else
        }

        SetWorldTransform(hDC, &previousXForm); // change world transform to the old value
    }
}

static void RedrawWindowArea(int left, int top, int right, int bottom, RECT &redrawRect, RECT &prevRedrawRect, bool isBall = false, bool clearBackground = FALSE)
{
    prevRedrawRect = redrawRect;

    if (isBall != true)
    {
        redrawRect.left = left * GLOBAL_SCALE;
        redrawRect.right = (right + left) * GLOBAL_SCALE;
        redrawRect.top = top * GLOBAL_SCALE;
        redrawRect.bottom = (bottom + top) * GLOBAL_SCALE;
    }
    else
    {
        redrawRect.left = left * GLOBAL_SCALE;
        redrawRect.right = right + redrawRect.left;
        redrawRect.top = top * GLOBAL_SCALE;
        redrawRect.bottom = bottom + redrawRect.top;
    }

    // set bg color on prev pos
    InvalidateRect(HWnd, &prevRedrawRect, clearBackground);

    // draw rect on new pos
    InvalidateRect(HWnd, &redrawRect, clearBackground);
}

static void RedrawPlatform()
{
    RedrawWindowArea(PlatformXPosition + LEVEL_X_OFFSET, PLATFORM_DEFAULT_Y_POSITION, PlatformWidth, PLATFORM_DEFAULT_HEIGHT, RedrawPlatformRect, RedrawPrevPlatformRect);
}

static void RedrawLevel()
{
    RedrawWindowArea(LEVEL_X_OFFSET, LEVEL_Y_OFFSET, CELL_WIDTH * LEVEL_MAX_ROWS, CELL_HEIGHT * LEVEL_MAX_BRICKS_IN_ROW, RedrawLevelRect, RedrawPrevLevelRect);
}

static void RedrawBall()
{
    RedrawWindowArea(BallXPosition + LEVEL_X_OFFSET, BallYPosition + LEVEL_Y_OFFSET, BALL_SIZE * GLOBAL_SCALE - 1, BALL_SIZE * GLOBAL_SCALE - 1, RedrawBallRect, RedrawPrevBallRect, true);
}

static void MoveBall()
{
    int nextBallXPosition, nextBallYPosition;

    nextBallXPosition = BallXPosition + (int)(BallSpeed * cos(BallDirection));
    nextBallYPosition = BallYPosition - (int)(BallSpeed * sin(BallDirection));

    if (nextBallXPosition < 0)
    {
        nextBallXPosition = -nextBallXPosition;
        BallDirection = M_PI - BallDirection;
    }

    if (nextBallYPosition < LEVEL_Y_OFFSET)
    {
        nextBallYPosition = LEVEL_Y_OFFSET - (nextBallYPosition - LEVEL_Y_OFFSET);
        BallDirection = -BallDirection;
    }

    if (nextBallXPosition > LEVEL_MAX_X_POSITION)
    {
        nextBallXPosition = LEVEL_MAX_X_POSITION - (nextBallXPosition - LEVEL_MAX_X_POSITION);
        BallDirection = M_PI - BallDirection;
    }

    if (nextBallYPosition > LEVEL_MAX_Y_POSITION)
    {
        nextBallYPosition = LEVEL_MAX_Y_POSITION - (nextBallYPosition - LEVEL_MAX_Y_POSITION);
        BallDirection = M_PI + (M_PI - BallDirection);
    }
        
    BallXPosition = nextBallXPosition;
    BallYPosition = nextBallYPosition;

    RedrawBall();
}

int OnKeyDown(EKeyType keyType)
{
    switch (keyType)
    {
    case EKT_LEFT:
    {
        PlatformXPosition -= PlatformXStep;
        break;
    }
    case EKT_RIGHT:
    {
        PlatformXPosition += PlatformXStep;
        break;
    }
    case EKT_SPACE:
    {
        break;
    }
    }
    RedrawPlatform();
    return 0;
}

int OnTimer()
{
    MoveBall();

    return 0;
}

void InitGame(HWND hWnd)
{
    HWnd = hWnd;

    SetTimer(hWnd, TIMER_ID, 50, NULL);

    SetPensAndBrushes();

    RedrawLevel();    
    RedrawPlatform();
    RedrawBall();
}

void DrawFrame(HDC hDC, RECT &paintArea) // draw new information in window
{    
    RECT intersectionRect{};

    if (IntersectRect(&intersectionRect, &paintArea, &RedrawLevelRect))
        CreateLevel(hDC, Level_01); // creating the prepared level with bricks and platform

    if (IntersectRect(&intersectionRect, &paintArea, &RedrawPlatformRect)) // redraw only specified area
        CreatePlatform(hDC, LEVEL_X_OFFSET + PlatformXPosition, PLATFORM_DEFAULT_Y_POSITION);
    
    if (IntersectRect(&intersectionRect, &paintArea, &RedrawBallRect))
        CreateBall(hDC);

    /*
    * Brick animation
    */
    //SetGraphicsMode(hDC, GM_ADVANCED); // using for SetWorldTransform()
    //
    //for (int i = 0; i < 16; i++)
    //{
    //    CreateAnimatedBrick(hDC, 20 + i * CELL_WIDTH, 100, EBT_SECOND, ELT_FIRST, i);
    //    CreateAnimatedBrick(hDC, 20 + i * CELL_WIDTH, 130, EBT_FIRST, ELT_FIRST, i);
    //}
    
}