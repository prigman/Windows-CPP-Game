#include "Engine.h"

/* FIRST LEVEL, BRICKS POSITION */

char Level_01[SGameEngine::LEVEL_MAX_ROWS][SGameEngine::LEVEL_MAX_BRICKS_IN_ROW] =
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

SGameEngine::SGameEngine()
    : 

    HWnd(nullptr),

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
    LevelBorderThirdBrush(nullptr),

    RedrawPlatformRect{0, 0, 0, 0},
    RedrawPrevPlatformRect{0, 0, 0, 0},
    RedrawLevelRect{0, 0, 0, 0},
    RedrawPrevLevelRect{0, 0, 0, 0},
    RedrawBallRect{0, 0, 0, 0},
    RedrawPrevBallRect{0, 0, 0, 0},
    RedrawBordersRect{0, 0, 0, 0},
    RedrawPrevBordersRect{0, 0, 0, 0},


    PlatformInnerWidth(PLATFORM_DEFAULT_INNER_WIDTH),
    PlatformXPosition(PLATFORM_DEFAULT_X_POSITION),
    PlatformXStep(GLOBAL_SCALE * 2),

    PlatformWidth(PLATFORM_DEFAULT_WIDTH),

    BallXPosition(BALL_DEFAULT_X_POSITION),
    BallYPosition(BALL_DEFAULT_Y_POSITION),

    BallSpeed(3.0), 
    BallDirection(M_PI - M_PI_4)
{}

void SGameEngine::InitGame(HWND hWnd)
{
    HWnd = hWnd;

    SetTimer(hWnd, TIMER_ID, 50, NULL);

    SetPensAndBrushes();

    RedrawLevel();    
    RedrawPlatform();
    RedrawBall();
    RedrawBorders();
}

// draw new information in window
void SGameEngine::DrawFrame(HDC hDC, RECT &paintArea)
{    
    RECT intersectionRect{};

    if (IntersectRect(&intersectionRect, &paintArea, &RedrawLevelRect))
        CreateLevel(hDC, Level_01); // creating the prepared level with bricks and platform

    if (IntersectRect(&intersectionRect, &paintArea, &RedrawPlatformRect)) // redraw only specified area
        CreatePlatform(hDC, PlatformXPosition, PLATFORM_DEFAULT_Y_POSITION);

    if (IntersectRect(&intersectionRect, &paintArea, &RedrawBallRect))
        CreateBall(hDC);

    if (IntersectRect(&intersectionRect, &paintArea, &RedrawBordersRect))
        CreateBounds(hDC);

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

int SGameEngine::OnTimer()
{
    MoveBall();

    return 0;
}

int SGameEngine::OnKeyDown(EKeyType keyType)
{
    switch (keyType)
    {
    case EKT_LEFT:
    {
        PlatformXPosition -= PlatformXStep;
        if (PlatformXPosition < LEVEL_BORDER_X_OFFSET)
            PlatformXPosition = LEVEL_BORDER_X_OFFSET;
        RedrawPlatform();
        break;
    }
    case EKT_RIGHT:
    {
        PlatformXPosition += PlatformXStep;
        if (PlatformXPosition > LEVEL_MAX_X_POSITION - PlatformWidth + 1)
            PlatformXPosition = LEVEL_MAX_X_POSITION - PlatformWidth + 1;
        RedrawPlatform();
        break;
    }
    case EKT_SPACE:
    {
        break;
    }
    }
    return 0;
}

void SGameEngine::CreateEllipse(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale)
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

void SGameEngine::CreateRoundedRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, int borderRound, bool useGlobalScale)
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

void SGameEngine::CreateRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale)
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

void SGameEngine::CreateArc(HDC hDC, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, HPEN pen)
{
    SelectObject(hDC, pen);
    Arc(hDC, x1 * GLOBAL_SCALE, y1 * GLOBAL_SCALE, x2 * GLOBAL_SCALE, y2 * GLOBAL_SCALE, x3 * GLOBAL_SCALE, y3 * GLOBAL_SCALE, x4 * GLOBAL_SCALE, y4 * GLOBAL_SCALE);
}

void SGameEngine::CreatePlatform(HDC hDC, int posX, int posY)
{
    // draw a background before creating a platform
    CreateRect(hDC, RedrawPrevPlatformRect.left, RedrawPrevPlatformRect.top, RedrawPrevPlatformRect.right, RedrawPrevPlatformRect.bottom, BackgroundPen, BackgroundBrush, false);

    int platformXOffset = 4;
    int platformYOffset = 1;

    int platformHeight = 5;

    CreateEllipse(hDC, posX, posY, posX + PLATFORM_CIRCLE_SIZE, posY + PLATFORM_CIRCLE_SIZE, FirstColorPen, FirstColorBrush, true);
    CreateEllipse(hDC, posX + PlatformInnerWidth, posY, posX + PLATFORM_CIRCLE_SIZE + PlatformInnerWidth, posY + PLATFORM_CIRCLE_SIZE, FirstColorPen, FirstColorBrush, true);

    CreateRoundedRect(hDC, posX + platformXOffset, posY + platformYOffset, posX + platformXOffset + PlatformInnerWidth - 1, posY + platformYOffset + platformHeight, SecondColorPen, SecondColorBrush, PLATFORM_BORDER_ROUND, true);

    // draw highlight on the ellipse
    CreateArc(hDC, posX + 1, posY + 1, posX + PLATFORM_CIRCLE_SIZE - 1, posY + PLATFORM_CIRCLE_SIZE - 1, posX + 1 + 1, posY + 1, posX + 1, posY + 1 + 2, WhiteColorPen);
}

void SGameEngine::CreateBall(HDC hDC)
{
    // draw a background before creating a platform
    CreateEllipse(hDC, RedrawPrevBallRect.left, RedrawPrevBallRect.top, RedrawPrevBallRect.right, RedrawPrevBallRect.bottom, BackgroundPen, BackgroundBrush, false);

    CreateEllipse(hDC, RedrawBallRect.left, RedrawBallRect.top, RedrawBallRect.right, RedrawBallRect.bottom, WhiteColorPen, WhiteColorBrush, false);
}

void SGameEngine::CreateBrick(HDC hDC, int posX, int posY, EBrickType brickColorType) // create brick based on its color type
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

void SGameEngine::CreateLevel(HDC hDC, char level[SGameEngine::LEVEL_MAX_ROWS][SGameEngine::LEVEL_MAX_BRICKS_IN_ROW]) // draw bricks in rows
{
    for (int i = 0; i < LEVEL_MAX_ROWS; i++)
        for (int j = 0; j < LEVEL_MAX_BRICKS_IN_ROW; j++)
            CreateBrick(hDC, LEVEL_X_OFFSET + j * CELL_WIDTH, LEVEL_Y_OFFSET + i * CELL_HEIGHT, (EBrickType)level[i][j]);
}

void SGameEngine::CreatePenAndBrush(unsigned char red, unsigned char green, unsigned char blue, HPEN &pen, HBRUSH &brush)
{
    pen = CreatePen(PS_SOLID, 0, RGB(red, green, blue));
    brush = CreateSolidBrush(RGB(red, green, blue));
}

void SGameEngine::SetPensAndBrushes()
{
    CreatePenAndBrush(128, 255, 255, LevelBorderFirstPen, LevelBorderFirstBrush);
    CreatePenAndBrush(255, 255, 255, LevelBorderSecondPen, LevelBorderSecondBrush);
    CreatePenAndBrush(0, 0, 0, LevelBorderThirdPen, LevelBorderThirdBrush);
    CreatePenAndBrush(255, 255, 255, WhiteColorPen, WhiteColorBrush);
    LetterPen = CreatePen(PS_SOLID, GLOBAL_SCALE, RGB(255, 255, 255));
    CreatePenAndBrush(BG_RGB_RED, BG_RGB_GREEN, BG_RGB_BLUE, BackgroundPen, BackgroundBrush); // backround color
    CreatePenAndBrush(255, 128, 255, FirstColorPen, FirstColorBrush); // purple color
    CreatePenAndBrush(128, 255, 255, SecondColorPen, SecondColorBrush); // cyan color
}

void SGameEngine::CreateAnimatedBrick(HDC hDC, int posX, int posY, EBrickType brickType, ELetterType letterType, int rotationStep)
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

void SGameEngine::RedrawWindowArea(int left, int top, int right, int bottom, RECT &redrawRect, RECT &prevRedrawRect, bool isBall, bool clearBackground) const
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

void SGameEngine::RedrawPlatform()
{
    RedrawWindowArea(PlatformXPosition, PLATFORM_DEFAULT_Y_POSITION, PlatformWidth, PLATFORM_DEFAULT_HEIGHT, RedrawPlatformRect, RedrawPrevPlatformRect);
}

void SGameEngine::RedrawLevel()
{
    RedrawWindowArea(LEVEL_X_OFFSET, LEVEL_Y_OFFSET, CELL_WIDTH * LEVEL_MAX_BRICKS_IN_ROW, CELL_HEIGHT * LEVEL_MAX_ROWS, RedrawLevelRect, RedrawPrevLevelRect);
}

void SGameEngine::RedrawBall()
{
    RedrawWindowArea(BallXPosition, BallYPosition, BALL_SIZE * GLOBAL_SCALE - 1, BALL_SIZE * GLOBAL_SCALE - 1, RedrawBallRect, RedrawPrevBallRect, true);
}

void SGameEngine::RedrawBorders()
{
    RedrawWindowArea(LEVEL_BORDER_X_OFFSET, LEVEL_BORDER_Y_OFFSET, LEVEL_BORDER_TILE_WIDTH, LEVEL_BORDER_TILE_HEIGHT, RedrawBordersRect, RedrawPrevBordersRect);
}

void SGameEngine::MoveBall()
{
    int nextBallXPosition, nextBallYPosition, 
        maxXPosition = LEVEL_MAX_X_POSITION - BALL_SIZE, platformYPosition = PLATFORM_DEFAULT_Y_POSITION - BALL_SIZE;

    nextBallXPosition = BallXPosition + (int)(BallSpeed * cos(BallDirection));
    nextBallYPosition = BallYPosition - (int)(BallSpeed * sin(BallDirection));

    if (nextBallXPosition < LEVEL_BORDER_X_OFFSET)
    {
        nextBallXPosition = LEVEL_BORDER_X_OFFSET - (nextBallXPosition - LEVEL_BORDER_X_OFFSET);
        BallDirection = M_PI - BallDirection;
    }

    if (nextBallYPosition < LEVEL_BORDER_Y_OFFSET)
    {
        nextBallYPosition = LEVEL_BORDER_Y_OFFSET - (nextBallYPosition - LEVEL_BORDER_Y_OFFSET);
        BallDirection = -BallDirection;
    }

    if (nextBallXPosition > maxXPosition)
    {
        nextBallXPosition = maxXPosition - (nextBallXPosition - maxXPosition);
        BallDirection = M_PI - BallDirection;
    }

    if (nextBallYPosition > LEVEL_MAX_Y_POSITION)
    {
        nextBallYPosition = LEVEL_MAX_Y_POSITION - (nextBallYPosition - LEVEL_MAX_Y_POSITION);
        BallDirection = M_PI + (M_PI - BallDirection);
    }

    if (nextBallYPosition > platformYPosition)
    {
        if (nextBallXPosition >= PlatformXPosition && nextBallXPosition <= PlatformXPosition + PlatformWidth)
        {
            nextBallYPosition = platformYPosition - (nextBallYPosition - platformYPosition);
            BallDirection = M_PI + (M_PI - BallDirection);
        }
    }

    CheckLevelBrickHit(nextBallYPosition);
        
    BallXPosition = nextBallXPosition;
    BallYPosition = nextBallYPosition;

    RedrawBall();
}

void SGameEngine::CreateLevelBorder(HDC hDC, int posX, int posY, bool is_horizontal_line)
{
    if (is_horizontal_line)
    {
        CreateRect(hDC, posX, posY, posX + LEVEL_BORDER_TILE_WIDTH, posY + LEVEL_BORDER_TILE_HEIGHT, LevelBorderFirstPen, LevelBorderFirstBrush, true);
        CreateRect(hDC, posX, posY, posX + LEVEL_BORDER_TILE_WIDTH, posY + 1, LevelBorderSecondPen, LevelBorderSecondBrush, true);
        CreateRect(hDC, posX + LEVEL_BORDER_TILE_WIDTH / 2, posY + LEVEL_BORDER_TILE_HEIGHT / 2, posX + LEVEL_BORDER_TILE_WIDTH / 2 + 1, posY + LEVEL_BORDER_TILE_HEIGHT / 2 + 1, LevelBorderThirdPen, LevelBorderThirdBrush, true);
    }
    else
    {
        CreateRect(hDC, posX, posY, posX + LEVEL_BORDER_TILE_WIDTH, posY + LEVEL_BORDER_TILE_HEIGHT, LevelBorderFirstPen, LevelBorderFirstBrush, true);
        CreateRect(hDC, posX, posY, posX + 1, posY + LEVEL_BORDER_TILE_HEIGHT, LevelBorderSecondPen, LevelBorderSecondBrush, true);
        CreateRect(hDC, posX + LEVEL_BORDER_TILE_WIDTH / 2, posY + LEVEL_BORDER_TILE_HEIGHT / 2, posX + LEVEL_BORDER_TILE_WIDTH / 2 + 1, posY + LEVEL_BORDER_TILE_HEIGHT / 2 - 1, LevelBorderThirdPen, LevelBorderThirdBrush, true);
    }
}

void SGameEngine::CreateBounds(HDC hDC)
{
    // right border
    for (int i = 0; i < (LEVEL_MAX_Y_POSITION * GLOBAL_SCALE) / (LEVEL_BORDER_TILE_HEIGHT * GLOBAL_SCALE) + LEVEL_BORDER_TOP_MARGIN + 2; i++)
        CreateLevelBorder(hDC, LEVEL_MAX_X_POSITION + LEVEL_BORDER_RIGHT_MARGIN, i * LEVEL_BORDER_TILE_HEIGHT + LEVEL_BORDER_TOP_MARGIN, false);

    // left border
    for (int i = 0; i < (LEVEL_MAX_Y_POSITION * GLOBAL_SCALE) / (LEVEL_BORDER_TILE_HEIGHT * GLOBAL_SCALE) + LEVEL_BORDER_TOP_MARGIN + 2; i++)
        CreateLevelBorder(hDC, LEVEL_BORDER_LEFT_MARGIN, i * LEVEL_BORDER_TILE_HEIGHT + LEVEL_BORDER_TOP_MARGIN, false);

    // top border
    for (int i = 0; i < ((LEVEL_MAX_X_POSITION - LEVEL_BORDER_TILE_WIDTH) * GLOBAL_SCALE) / (LEVEL_BORDER_TILE_WIDTH * GLOBAL_SCALE) + LEVEL_BORDER_LEFT_MARGIN - 1; i++)
        CreateLevelBorder(hDC, i * LEVEL_BORDER_TILE_WIDTH + LEVEL_BORDER_LEFT_MARGIN + 1, 0, true);

    // bottom border
   /* for (int i = 0; i < (LEVEL_MAX_X_POSITION * GLOBAL_SCALE) / (LEVEL_BORDER_TILE_WIDTH * GLOBAL_SCALE) + LEVEL_BORDER_LEFT_MARGIN - 1; i++)
        CreateLevelBorder(hDC, i * LEVEL_BORDER_TILE_WIDTH + LEVEL_BORDER_LEFT_MARGIN + 1, LEVEL_MAX_Y_POSITION, true);*/

}

void SGameEngine::CheckLevelBrickHit(int& nextBallYPosition)
{
    int brickYPosition = LEVEL_Y_OFFSET + LEVEL_MAX_ROWS * CELL_HEIGHT;

    for (int i = LEVEL_MAX_ROWS - 1; i >= 0; i--)
    {
        for (int j = 0; j < LEVEL_MAX_BRICKS_IN_ROW; j++)
        {
            if (Level_01[i][j] == 0)
                continue;

            else if (nextBallYPosition < brickYPosition)
            {
                nextBallYPosition = brickYPosition - (nextBallYPosition - brickYPosition);
                BallDirection = -BallDirection;
            }
        }
        brickYPosition -= CELL_HEIGHT;
    }
}