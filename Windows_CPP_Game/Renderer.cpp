
#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "Level.h"
#include "Border.h"

#include "Renderer.h"

SRenderer::SRenderer()
    :
    hWnd(nullptr),

    firstColorPen(nullptr),
    secondColorPen(nullptr),
    whiteColorPen(nullptr),
    fadeColorPen(nullptr),
    letterPen(nullptr),
    backgroundPen(nullptr),
    levelBorderFirstPen(nullptr),
    levelBorderSecondPen(nullptr),
    levelBorderThirdPen(nullptr),

    backgroundBrush(nullptr),
    firstColorBrush(nullptr),
    secondColorBrush(nullptr),
    whiteColorBrush(nullptr),
    fadeColorBrush(nullptr),
    levelBorderFirstBrush(nullptr),
    levelBorderSecondBrush(nullptr),
    levelBorderThirdBrush(nullptr)

{}

void SRenderer::CreateEllipse(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale)
{
    if (useGlobalScale)
    {
        left *= SConfig::GLOBAL_SCALE;
        top *= SConfig::GLOBAL_SCALE;
        right *= SConfig::GLOBAL_SCALE;
        bottom *= SConfig::GLOBAL_SCALE;
    }
    SelectObject(hDC, pen);
    if (brush != 0)
        SelectObject(hDC, brush);
    Ellipse(hDC, left, top, right, bottom);
}

void SRenderer::CreateRoundedRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, int borderRound, bool useGlobalScale)
{
    if (useGlobalScale)
    {
        left *= SConfig::GLOBAL_SCALE;
        top *= SConfig::GLOBAL_SCALE;
        right *= SConfig::GLOBAL_SCALE;
        bottom *= SConfig::GLOBAL_SCALE;
    }
    SelectObject(hDC, pen);
    if (brush != 0)
        SelectObject(hDC, brush);
    RoundRect(hDC, left, top, right, bottom, borderRound, borderRound);
}

void SRenderer::CreateRect(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale)
{
    /*
    * Example of drawing a rectangle:
    * 
    // CreateRect(hDC, 20, 50, 20 + BRICK_WIDTH, 50 + BRICK_HEIGHT, EngineRenderer.firstColorPen, EngineRenderer.firstColorBrush, true);
    * 
    * left, right = x coord | top, bottom = y coord
    * x, y can be modified by the width and height of the shape
    */
    if (useGlobalScale)
    {
        left *= SConfig::GLOBAL_SCALE;
        top *= SConfig::GLOBAL_SCALE;
        right *= SConfig::GLOBAL_SCALE;
        bottom *= SConfig::GLOBAL_SCALE;
    }
    SelectObject(hDC, pen);
    // if not brush then draw only a border of the shape
    if (brush != 0)
        SelectObject(hDC, brush);
    Rectangle(hDC, left, top, right, bottom);
}

void SRenderer::CreateArc(HDC hDC, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, HPEN pen)
{
    SelectObject(hDC, pen);
    Arc(hDC, x1 * SConfig::GLOBAL_SCALE, y1 * SConfig::GLOBAL_SCALE, x2 * SConfig::GLOBAL_SCALE, y2 * SConfig::GLOBAL_SCALE, x3 * SConfig::GLOBAL_SCALE, y3 * SConfig::GLOBAL_SCALE, x4 * SConfig::GLOBAL_SCALE, y4 * SConfig::GLOBAL_SCALE);
}

void SRenderer::CreateLevelBorder(HDC hDC, Vector2 position, bool is_horizontal_line)
{
    if (is_horizontal_line)
    {
        CreateRect(hDC, position.x, position.y, position.x + SConfig::BORDER_TILE_WIDTH, position.y + SConfig::BORDER_TILE_HEIGHT, levelBorderFirstPen, levelBorderFirstBrush, true);
        CreateRect(hDC, position.x, position.y, position.x + SConfig::BORDER_TILE_WIDTH, position.y + 1, levelBorderSecondPen, levelBorderSecondBrush, true);
        CreateRect(hDC, position.x + SConfig::BORDER_TILE_WIDTH / 2, position.y + SConfig::BORDER_TILE_HEIGHT / 2, position.x + SConfig::BORDER_TILE_WIDTH / 2 + 1, position.y + SConfig::BORDER_TILE_HEIGHT / 2 + 1, levelBorderThirdPen, levelBorderThirdBrush, true);
    }
    else
    {
        CreateRect(hDC, position.x, position.y, position.x + SConfig::BORDER_TILE_WIDTH, position.y + SConfig::BORDER_TILE_HEIGHT, levelBorderFirstPen, levelBorderFirstBrush, true);
        CreateRect(hDC, position.x, position.y, position.x + 1, position.y + SConfig::BORDER_TILE_HEIGHT, levelBorderSecondPen, levelBorderSecondBrush, true);
        CreateRect(hDC, position.x + SConfig::BORDER_TILE_WIDTH / 2, position.y + SConfig::BORDER_TILE_HEIGHT / 2, position.x + SConfig::BORDER_TILE_WIDTH / 2 + 1, position.y + SConfig::BORDER_TILE_HEIGHT / 2 - 1, levelBorderThirdPen, levelBorderThirdBrush, true);
    }
}

void SRenderer::DrawFrame(HDC hDC, RECT &paintArea, Level *level, Platform *platform, Ball *ball, Brick *brick, Border *border)
{    
    RECT intersectionRect{};

    // redraw only specified area

    if (IntersectRect(&intersectionRect, &paintArea, &level->redrawRect))
        // creating the prepared level with bricks
        CreateLevel(hDC, level->Level_01);

    if (IntersectRect(&intersectionRect, &paintArea, &brick->redrawRect))
        CreateBrick(hDC, brick->position, EBT_FADED);

    if (IntersectRect(&intersectionRect, &paintArea, &platform->redrawRect))
        CreatePlatform(hDC, platform->position, platform->platformInnerWidth, platform->redrawPrevRect);

    if (IntersectRect(&intersectionRect, &paintArea, &ball->redrawRect))
        CreateBall(hDC, ball->redrawRect, ball->redrawPrevRect);

    if (IntersectRect(&intersectionRect, &paintArea, &border->redrawRect))
        CreateBounds(hDC);

    /*
    * Brick animation
    */
    //SetGraphicsMode(hDC, GM_ADVANCED); // using for SetWorldTransform()
    //
    //for (int i = 0; i < 16; i++)
    //{
    //    CreateAnimatedBrick(hDC, Vector2(20 + i * Level::CELL_WIDTH, 100), &engine->objectBrick, EBT_SECOND, ELT_FIRST, i);
    //    CreateAnimatedBrick(hDC, Vector2(20 + i * Level::CELL_WIDTH, 130), &engine->objectBrick, EBT_FIRST, ELT_FIRST, i);
    //}

}

void SRenderer::CreatePenAndBrush(unsigned char red, unsigned char green, unsigned char blue, HPEN &pen, HBRUSH &brush)
{
    pen = CreatePen(PS_SOLID, 0, RGB(red, green, blue));
    brush = CreateSolidBrush(RGB(red, green, blue));
}

void SRenderer::SetPensAndBrushes()
{
    CreatePenAndBrush(128, 255, 255, levelBorderFirstPen, levelBorderFirstBrush);
    CreatePenAndBrush(255, 255, 255, levelBorderSecondPen, levelBorderSecondBrush);
    CreatePenAndBrush(0, 0, 0, levelBorderThirdPen, levelBorderThirdBrush);
    CreatePenAndBrush(255, 255, 255, whiteColorPen, whiteColorBrush);
    letterPen = CreatePen(PS_SOLID, SConfig::GLOBAL_SCALE, RGB(255, 255, 255));
    CreatePenAndBrush(BG_RGB_RED, BG_RGB_GREEN, BG_RGB_BLUE, backgroundPen, backgroundBrush); // backround color
    CreatePenAndBrush(255, 128, 255, firstColorPen, firstColorBrush); // purple color
    CreatePenAndBrush(128, 255, 255, secondColorPen, secondColorBrush); // cyan color
}

void SRenderer::CreateBrick(HDC hDC, Vector2 position, EBrickType brickColorType) // create brick based on its color type
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
        pen = firstColorPen;
        brush = firstColorBrush;
        break;
    }
    case EBT_SECOND:
    {
        pen = secondColorPen;
        brush = secondColorBrush;
        break;
    }
    case EBT_FADED:
    {
        pen = fadeColorPen;
        brush = fadeColorBrush;
        break;
    }
    default:
    {
        return;
    }
    }

    CreateRoundedRect(hDC, position.x, position.y, position.x + SConfig::BRICK_WIDTH, position.y + SConfig::BRICK_HEIGHT, pen, brush, SConfig::BRICK_BORDER_ROUND, true);
}

void SRenderer::CreateAnimatedBrick(HDC hDC, Vector2 position, int brickWidth, EBrickType brickType, ELetterType letterType, int rotationStep)
{
    position.x *= SConfig::GLOBAL_SCALE;

    double rotationAngle; // converting step to rotation angle
    double offset = 0.0;

    int brickHalfHeight = SConfig::BRICK_HEIGHT / 2 * SConfig::GLOBAL_SCALE;
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
            frontColorPen = firstColorPen;
            frontColorBrush = firstColorBrush;

            backColorPen = secondColorPen;
            backColorBrush = secondColorBrush;
            break;
        }
        default:
        {
            frontColorPen = secondColorPen;
            frontColorBrush = secondColorBrush;

            backColorPen = firstColorPen;
            backColorBrush = firstColorBrush;
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
            frontColorPen = firstColorPen;
            frontColorBrush = firstColorBrush;

            backColorPen = secondColorPen;
            backColorBrush = secondColorBrush;
            break;
        }
        default:
        {
            frontColorPen = secondColorPen;
            frontColorBrush = secondColorBrush;

            backColorPen = firstColorPen;
            backColorBrush = firstColorBrush;
            break;
        }
        }
    }

    if (rotationStep == 4 || rotationStep == 12)
    {
        // background output
        CreateRect(hDC, position.x, position.y + brickHalfHeight - SConfig::GLOBAL_SCALE, position.x + SConfig::BRICK_WIDTH * SConfig::GLOBAL_SCALE, position.y + brickHalfHeight, backColorPen, backColorBrush, false); // 0, 0 because of xForm's eDx, eDy
        // front side output
        CreateRect(hDC, position.x, position.y + brickHalfHeight, position.x + brickWidth * SConfig::GLOBAL_SCALE, position.y + brickHalfHeight + SConfig::GLOBAL_SCALE - 1, frontColorPen, frontColorBrush, false); // 0, 0 because of xForm's eDx, eDy
    }
    else
    {
        //rotation matrix of the brick
        xForm.eM11 = 1.0f;
        xForm.eM12 = 0.0f;
        xForm.eM21 = 0.0f;
        xForm.eM22 = (float) cos(rotationAngle);
        xForm.eDx  = (float) position.x; // coord x
        xForm.eDy  = (float) position.y + (float) brickHalfHeight; // coord y

        SetWorldTransform(hDC, &xForm); // change world transform to the new value


        offset = 3.0 * (1.0 - fabs(xForm.eM22)) * (double)SConfig::GLOBAL_SCALE;
        brickBackPartOffset = (int)round(offset);

        //background output
        CreateRect(hDC, 0, -brickHalfHeight - brickBackPartOffset, brickWidth * SConfig::GLOBAL_SCALE, brickHalfHeight - brickBackPartOffset, backColorPen, backColorBrush, false); // 0, 0 because of xForm's eDx, eDy


        // front side output
        CreateRect(hDC, 0, -brickHalfHeight, SConfig::BRICK_WIDTH * SConfig::GLOBAL_SCALE, brickHalfHeight, frontColorPen, frontColorBrush, false); // 0, 0 because of xForm's eDx, eDy

        if (rotationStep > 4 && rotationStep <= 12)
        {
            if (letterType == ELT_FIRST)
                CreateEllipse(hDC, 0 + 5 * SConfig::GLOBAL_SCALE, (-5 * SConfig::GLOBAL_SCALE) / 2, 0 + 10 * SConfig::GLOBAL_SCALE, 5 * SConfig::GLOBAL_SCALE / 2, letterPen, NULL, false);
            // else
        }

        SetWorldTransform(hDC, &previousXForm); // change world transform to the old value
    }
}

void SRenderer::CreateLevel(HDC hDC, const char level[SConfig::LEVEL_MAX_ROWS][SConfig::LEVEL_MAX_BRICKS_IN_ROW]) // draw bricks in rows
{
    for (int i = 0; i < SConfig::LEVEL_MAX_ROWS; i++)
        for (int j = 0; j < SConfig::LEVEL_MAX_BRICKS_IN_ROW; j++)
            CreateBrick(hDC, Vector2(SConfig::LEVEL_X_OFFSET + j * SConfig::CELL_WIDTH, SConfig::LEVEL_Y_OFFSET + i * SConfig::CELL_HEIGHT), (EBrickType)level[i][j]);
}

void SRenderer::CreatePlatform(HDC hDC, Vector2 platformPosition, int platformInnerWidth, RECT redrawPrevRect)
{
    // draw a background before creating a platform
    CreateRect(hDC, redrawPrevRect.left, redrawPrevRect.top, redrawPrevRect.right, redrawPrevRect.bottom, backgroundPen, backgroundBrush, false);

    int platformXOffset = 4;
    int platformYOffset = 1;

    int platformHeight = 5;

    CreateEllipse(hDC, platformPosition.x, platformPosition.y, platformPosition.x + SConfig::PLATFORM_ELLIPSE_SIZE, platformPosition.y + SConfig::PLATFORM_ELLIPSE_SIZE, firstColorPen, firstColorBrush, true);
    CreateEllipse(hDC, platformPosition.x + platformInnerWidth, platformPosition.y, platformPosition.x + SConfig::PLATFORM_ELLIPSE_SIZE + platformInnerWidth, platformPosition.y + SConfig::PLATFORM_ELLIPSE_SIZE, firstColorPen, firstColorBrush, true);

    CreateRoundedRect(hDC, platformPosition.x + platformXOffset, platformPosition.y + platformYOffset, platformPosition.x + platformXOffset + platformInnerWidth - 1, platformPosition.y + platformYOffset + platformHeight, secondColorPen, secondColorBrush, SConfig::PLATFORM_BORDER_ROUND, true);

    // draw highlight on the ellipse
    CreateArc(hDC, platformPosition.x + 1, platformPosition.y + 1, platformPosition.x + SConfig::PLATFORM_ELLIPSE_SIZE - 1, platformPosition.y + SConfig::PLATFORM_ELLIPSE_SIZE - 1, platformPosition.x + 1 + 1, platformPosition.y + 1, platformPosition.x + 1, platformPosition.y + 1 + 2, whiteColorPen);
}

void SRenderer::CreateBall(HDC hDC, RECT redrawRect, RECT redrawPrevRect)
{
    // draw a background before creating a platform
    CreateEllipse(hDC, redrawPrevRect.left, redrawPrevRect.top, redrawPrevRect.right, redrawPrevRect.bottom, backgroundPen, backgroundBrush, false);

    CreateEllipse(hDC, redrawRect.left, redrawRect.top, redrawRect.right, redrawRect.bottom, whiteColorPen, whiteColorBrush, false);
}

void SRenderer::CreateBounds(HDC hDC)
{
    // right border
    for (int i = 0; i < (SConfig::LEVEL_MAX_Y_POSITION * SConfig::GLOBAL_SCALE) / (SConfig::BORDER_TILE_HEIGHT * SConfig::GLOBAL_SCALE) + SConfig::BORDER_TOP_MARGIN + 2; i++)
        CreateLevelBorder(hDC, Vector2(SConfig::LEVEL_MAX_X_POSITION + SConfig::BORDER_RIGHT_MARGIN, i * SConfig::BORDER_TILE_HEIGHT + SConfig::BORDER_TOP_MARGIN), false);

    // left border
    for (int i = 0; i < (SConfig::LEVEL_MAX_Y_POSITION * SConfig::GLOBAL_SCALE) / (SConfig::BORDER_TILE_HEIGHT * SConfig::GLOBAL_SCALE) + SConfig::BORDER_TOP_MARGIN + 2; i++)
        CreateLevelBorder(hDC, Vector2(SConfig::BORDER_LEFT_MARGIN, i * SConfig::BORDER_TILE_HEIGHT + SConfig::BORDER_TOP_MARGIN), false);

    // top border
    for (int i = 0; i < ((SConfig::LEVEL_MAX_X_POSITION - SConfig::BORDER_TILE_WIDTH) * SConfig::GLOBAL_SCALE) / (SConfig::BORDER_TILE_WIDTH * SConfig::GLOBAL_SCALE) + SConfig::BORDER_LEFT_MARGIN - 1; i++)
        CreateLevelBorder(hDC, Vector2(i * SConfig::BORDER_TILE_WIDTH + SConfig::BORDER_LEFT_MARGIN + 1, 0), true);

    // bottom border
    /* for (int i = 0; i < (LEVEL_MAX_X_POSITION * GLOBAL_SCALE) / (LEVEL_BORDER_TILE_WIDTH * GLOBAL_SCALE) + LEVEL_BORDER_LEFT_MARGIN - 1; i++)
    CreateLevelBorder(hDC, i * LEVEL_BORDER_TILE_WIDTH + LEVEL_BORDER_LEFT_MARGIN + 1, LEVEL_MAX_Y_POSITION, true);*/

}

void SRenderer::RedrawWindowArea(int left, int top, int right, int bottom, RECT &redrawRect, RECT &prevRedrawRect, bool isBallObject, BOOL clearBackground) const
{
    prevRedrawRect = redrawRect;

    if (isBallObject != true)
    {
        redrawRect.left = left * SConfig::GLOBAL_SCALE;
        redrawRect.right = (right + left) * SConfig::GLOBAL_SCALE;
        redrawRect.top = top * SConfig::GLOBAL_SCALE;
        redrawRect.bottom = (bottom + top) * SConfig::GLOBAL_SCALE;
    }
    else
    {
        redrawRect.left = left * SConfig::GLOBAL_SCALE;
        redrawRect.right = right * SConfig::GLOBAL_SCALE - 1 + redrawRect.left;
        redrawRect.top = top * SConfig::GLOBAL_SCALE;
        redrawRect.bottom = bottom * SConfig::GLOBAL_SCALE - 1 + redrawRect.top;
    }

    // set bg color on prev pos
    InvalidateRect(hWnd, &prevRedrawRect, clearBackground);

    // draw rect on new pos
    InvalidateRect(hWnd, &redrawRect, clearBackground);
}