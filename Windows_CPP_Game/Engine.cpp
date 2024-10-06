#include "Engine.h"

Ball ObjectBall;
Brick ObjectBrick;
Platform ObjectPlatform;
Level ObjectLevel;
Border ObjectBorder;

void SGameEngine::InitGame(HWND hWnd)
{
    HWnd = hWnd;

    SetTimer(hWnd, TIMER_ID, 50, NULL);

    EngineRenderer.OnGameInitRenderer();
}

void SRenderer::OnGameInitRenderer()
{
    EngineRenderer.SetPensAndBrushes();

    EngineRenderer.RedrawGameObject(ObjectLevel);
    EngineRenderer.RedrawGameObject(ObjectPlatform);
    EngineRenderer.RedrawGameObject(ObjectBall);
    EngineRenderer.RedrawGameObject(ObjectBorder);
}

// draw new information in window
void SRenderer::DrawFrame(HDC hDC, RECT &paintArea)
{    
    RECT intersectionRect{};

    if (IntersectRect(&intersectionRect, &paintArea, &ObjectLevel.redrawRect))
        ObjectLevel.CreateLevel(hDC, ObjectLevel.Level_01); // creating the prepared level with bricks and platform

    if (IntersectRect(&intersectionRect, &paintArea, &ObjectPlatform.redrawRect)) // redraw only specified area
        EngineRenderer.CreatePlatform(hDC, ObjectPlatform.position, ObjectPlatform);

    if (IntersectRect(&intersectionRect, &paintArea, &ObjectBall.redrawRect))
        EngineRenderer.CreateBall(hDC, ObjectBall);

    if (IntersectRect(&intersectionRect, &paintArea, &ObjectBorder.redrawRect))
        EngineRenderer.CreateBounds(hDC);

    /*
    * Brick animation
    */
    //SetGraphicsMode(hDC, GM_ADVANCED); // using for SetWorldTransform()
    //
    //for (int i = 0; i < 16; i++)
    //{
    //    CreateAnimatedBrick(hDC, Vector2(20 + i * Level::CELL_WIDTH, 100), EBT_SECOND, ELT_FIRST, i);
    //    CreateAnimatedBrick(hDC, Vector2(20 + i * Level::CELL_WIDTH, 130), EBT_FIRST, ELT_FIRST, i);
    //}

}

int SGameEngine::OnTimer()
{
    ObjectBall.MoveBall(ObjectBall);

    return 0;
}

int SGameEngine::OnKeyDown(EKeyType keyType)
{
    switch (keyType)
    {
    case EKT_LEFT:
    {
        ObjectPlatform.position.x -= ObjectPlatform.platformXStep;
        if (ObjectPlatform.position.x < Border::BORDER_X_OFFSET)
            ObjectPlatform.position.x = Border::BORDER_X_OFFSET;
        EngineRenderer.RedrawGameObject(ObjectPlatform);
        break;
    }
    case EKT_RIGHT:
    {
        ObjectPlatform.position.x += ObjectPlatform.platformXStep;
        if (ObjectPlatform.position.x > Level::LEVEL_MAX_X_POSITION - ObjectPlatform.width + 1)
            ObjectPlatform.position.x = Level::LEVEL_MAX_X_POSITION - ObjectPlatform.width + 1;
        EngineRenderer.RedrawGameObject(ObjectPlatform);
        break;
    }
    case EKT_SPACE:
    {
        break;
    }
    }
    return 0;
}

void SRenderer::CreateEllipse(HDC hDC, int left, int top, int right, int bottom, HPEN pen, HBRUSH brush, bool useGlobalScale)
{
    if (useGlobalScale)
    {
        left *= SGameEngine::GLOBAL_SCALE;
        top *= SGameEngine::GLOBAL_SCALE;
        right *= SGameEngine::GLOBAL_SCALE;
        bottom *= SGameEngine::GLOBAL_SCALE;
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
        left *= SGameEngine::GLOBAL_SCALE;
        top *= SGameEngine::GLOBAL_SCALE;
        right *= SGameEngine::GLOBAL_SCALE;
        bottom *= SGameEngine::GLOBAL_SCALE;
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
    // CreateRect(hDC, 20, 50, 20 + BRICK_WIDTH, 50 + BRICK_HEIGHT, EngineRenderer.FirstColorPen, EngineRenderer.FirstColorBrush, true);
    * 
    * left, right = x coord | top, bottom = y coord
    * x, y can be modified by the width and height of the shape
    */
    if (useGlobalScale)
    {
        left *= SGameEngine::GLOBAL_SCALE;
        top *= SGameEngine::GLOBAL_SCALE;
        right *= SGameEngine::GLOBAL_SCALE;
        bottom *= SGameEngine::GLOBAL_SCALE;
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
    Arc(hDC, x1 * SGameEngine::GLOBAL_SCALE, y1 * SGameEngine::GLOBAL_SCALE, x2 * SGameEngine::GLOBAL_SCALE, y2 * SGameEngine::GLOBAL_SCALE, x3 * SGameEngine::GLOBAL_SCALE, y3 * SGameEngine::GLOBAL_SCALE, x4 * SGameEngine::GLOBAL_SCALE, y4 * SGameEngine::GLOBAL_SCALE);
}

void SRenderer::CreatePlatform(HDC hDC, Vector2 position, Platform &platform)
{
    // draw a background before creating a platform
    CreateRect(hDC, platform.redrawPrevRect.left, platform.redrawPrevRect.top, platform.redrawPrevRect.right, platform.redrawPrevRect.bottom, BackgroundPen, BackgroundBrush, false);

    int platformXOffset = 4;
    int platformYOffset = 1;

    int platformHeight = 5;

    CreateEllipse(hDC, position.x, position.y, position.x + Platform::PLATFORM_CIRCLE_SIZE, position.y + Platform::PLATFORM_CIRCLE_SIZE, FirstColorPen, FirstColorBrush, true);
    CreateEllipse(hDC, position.x + platform.platformInnerWidth, position.y, position.x + Platform::PLATFORM_CIRCLE_SIZE + platform.platformInnerWidth, position.y + Platform::PLATFORM_CIRCLE_SIZE, FirstColorPen, FirstColorBrush, true);

    CreateRoundedRect(hDC, position.x + platformXOffset, position.y + platformYOffset, position.x + platformXOffset + platform.platformInnerWidth - 1, position.y + platformYOffset + platformHeight, SecondColorPen, SecondColorBrush, Platform::PLATFORM_BORDER_ROUND, true);

    // draw highlight on the ellipse
    CreateArc(hDC, position.x + 1, position.y + 1, position.x + Platform::PLATFORM_CIRCLE_SIZE - 1, position.y + Platform::PLATFORM_CIRCLE_SIZE - 1, position.x + 1 + 1, position.y + 1, position.x + 1, position.y + 1 + 2, WhiteColorPen);
}

void SRenderer::CreateBall(HDC hDC, Ball &ball)
{
    // draw a background before creating a platform
    CreateEllipse(hDC, ball.redrawPrevRect.left, ball.redrawPrevRect.top, ball.redrawPrevRect.right, ball.redrawPrevRect.bottom, BackgroundPen, BackgroundBrush, false);

    CreateEllipse(hDC, ball.redrawRect.left, ball.redrawRect.top, ball.redrawRect.right, ball.redrawRect.bottom, WhiteColorPen, WhiteColorBrush, false);
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

    CreateRoundedRect(hDC, position.x, position.y, position.x + Brick::BRICK_WIDTH, position.y + Brick::BRICK_HEIGHT, pen, brush, Brick::BRICK_BORDER_ROUND, true);
}

void Level::CreateLevel(HDC hDC, char level[LEVEL_MAX_ROWS][LEVEL_MAX_BRICKS_IN_ROW]) // draw bricks in rows
{
    for (int i = 0; i < LEVEL_MAX_ROWS; i++)
        for (int j = 0; j < LEVEL_MAX_BRICKS_IN_ROW; j++)
            EngineRenderer.CreateBrick(hDC, Vector2(LEVEL_X_OFFSET + j * CELL_WIDTH, LEVEL_Y_OFFSET + i * CELL_HEIGHT), (EBrickType)level[i][j]);
}

void SRenderer::CreatePenAndBrush(unsigned char red, unsigned char green, unsigned char blue, HPEN &pen, HBRUSH &brush)
{
    pen = CreatePen(PS_SOLID, 0, RGB(red, green, blue));
    brush = CreateSolidBrush(RGB(red, green, blue));
}

void SRenderer::SetPensAndBrushes()
{
    CreatePenAndBrush(128, 255, 255, LevelBorderFirstPen, LevelBorderFirstBrush);
    CreatePenAndBrush(255, 255, 255, LevelBorderSecondPen, LevelBorderSecondBrush);
    CreatePenAndBrush(0, 0, 0, LevelBorderThirdPen, LevelBorderThirdBrush);
    CreatePenAndBrush(255, 255, 255, WhiteColorPen, WhiteColorBrush);
    LetterPen = CreatePen(PS_SOLID, SGameEngine::GLOBAL_SCALE, RGB(255, 255, 255));
    CreatePenAndBrush(BG_RGB_RED, BG_RGB_GREEN, BG_RGB_BLUE, BackgroundPen, BackgroundBrush); // backround color
    CreatePenAndBrush(255, 128, 255, FirstColorPen, FirstColorBrush); // purple color
    CreatePenAndBrush(128, 255, 255, SecondColorPen, SecondColorBrush); // cyan color
}

void SRenderer::CreateAnimatedBrick(HDC hDC, Vector2 position, EBrickType brickType, ELetterType letterType, int rotationStep)
{
    position.x *= SGameEngine::GLOBAL_SCALE;

    double rotationAngle; // converting step to rotation angle
    double offset = 0.0;

    int brickHalfHeight = Brick::BRICK_HEIGHT / 2 * SGameEngine::GLOBAL_SCALE;
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
            frontColorPen = EngineRenderer.FirstColorPen;
            frontColorBrush = EngineRenderer.FirstColorBrush;

            backColorPen = EngineRenderer.SecondColorPen;
            backColorBrush = EngineRenderer.SecondColorBrush;
            break;
        }
        default:
        {
            frontColorPen = EngineRenderer.SecondColorPen;
            frontColorBrush = EngineRenderer.SecondColorBrush;

            backColorPen = EngineRenderer.FirstColorPen;
            backColorBrush = EngineRenderer.FirstColorBrush;
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
            frontColorPen = EngineRenderer.FirstColorPen;
            frontColorBrush = EngineRenderer.FirstColorBrush;

            backColorPen = EngineRenderer.SecondColorPen;
            backColorBrush = EngineRenderer.SecondColorBrush;
            break;
        }
        default:
        {
            frontColorPen = EngineRenderer.SecondColorPen;
            frontColorBrush = EngineRenderer.SecondColorBrush;

            backColorPen = EngineRenderer.FirstColorPen;
            backColorBrush = EngineRenderer.FirstColorBrush;
            break;
        }
        }
    }

    if (rotationStep == 4 || rotationStep == 12)
    {
        // background output
        CreateRect(hDC, position.x, position.y + brickHalfHeight - SGameEngine::GLOBAL_SCALE, position.x + Brick::BRICK_WIDTH * SGameEngine::GLOBAL_SCALE, position.y + brickHalfHeight, backColorPen, backColorBrush, false); // 0, 0 because of xForm's eDx, eDy
        // front side output
        CreateRect(hDC, position.x, position.y + brickHalfHeight, position.x + ObjectBrick.width * SGameEngine::GLOBAL_SCALE, position.y + brickHalfHeight + SGameEngine::GLOBAL_SCALE - 1, frontColorPen, frontColorBrush, false); // 0, 0 because of xForm's eDx, eDy
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

   
        offset = 3.0 * (1.0 - fabs(xForm.eM22)) * (double)SGameEngine::GLOBAL_SCALE;
        brickBackPartOffset = (int)round(offset);

        //background output
        CreateRect(hDC, 0, -brickHalfHeight - brickBackPartOffset, ObjectBrick.width * SGameEngine::GLOBAL_SCALE, brickHalfHeight - brickBackPartOffset, backColorPen, backColorBrush, false); // 0, 0 because of xForm's eDx, eDy


        // front side output
        CreateRect(hDC, 0, -brickHalfHeight, ObjectBrick.BRICK_WIDTH * SGameEngine::GLOBAL_SCALE, brickHalfHeight, frontColorPen, frontColorBrush, false); // 0, 0 because of xForm's eDx, eDy

        if (rotationStep > 4 && rotationStep <= 12)
        {
            if (letterType == ELT_FIRST)
                CreateEllipse(hDC, 0 + 5 * SGameEngine::GLOBAL_SCALE, (-5 * SGameEngine::GLOBAL_SCALE) / 2, 0 + 10 * SGameEngine::GLOBAL_SCALE, 5 * SGameEngine::GLOBAL_SCALE / 2, LetterPen, NULL, false);
            // else
        }

        SetWorldTransform(hDC, &previousXForm); // change world transform to the old value
    }
}

void SRenderer::RedrawWindowArea(int left, int top, int right, int bottom, RECT &redrawRect, RECT &prevRedrawRect, bool isBall, bool clearBackground) const
{
    prevRedrawRect = redrawRect;

    if (isBall != true)
    {
        redrawRect.left = left * SGameEngine::GLOBAL_SCALE;
        redrawRect.right = (right + left) * SGameEngine::GLOBAL_SCALE;
        redrawRect.top = top * SGameEngine::GLOBAL_SCALE;
        redrawRect.bottom = (bottom + top) * SGameEngine::GLOBAL_SCALE;
    }
    else
    {
        redrawRect.left = left * SGameEngine::GLOBAL_SCALE;
        redrawRect.right = right + redrawRect.left;
        redrawRect.top = top * SGameEngine::GLOBAL_SCALE;
        redrawRect.bottom = bottom + redrawRect.top;
    }

    // set bg color on prev pos
    InvalidateRect(Engine.HWnd, &prevRedrawRect, clearBackground);

    // draw rect on new pos
    InvalidateRect(Engine.HWnd, &redrawRect, clearBackground);
}

void SRenderer::RedrawGameObject(GameObject &gameObject) const
{
    RedrawWindowArea(gameObject.position.x, gameObject.position.y, gameObject.width, gameObject.height, gameObject.redrawRect, gameObject.redrawPrevRect);
}

//void Platform::RedrawPlatform()
//{
//    RedrawWindowArea(position.x, PLATFORM_DEFAULT_Y_POSITION, width, height, EngineRenderer.RedrawPlatformRect, EngineRenderer.RedrawPrevPlatformRect);
//}
//
//void Level::RedrawLevel(Level &level)
//{
//    EngineRenderer.RedrawWindowArea(LEVEL_X_OFFSET, LEVEL_Y_OFFSET, CELL_WIDTH * LEVEL_MAX_BRICKS_IN_ROW, CELL_HEIGHT * LEVEL_MAX_ROWS, GameLevel.redrawRect, GameLevel.redrawPrevRect);
//}

//void Ball::RedrawBall()
//{
//    EngineRenderer.RedrawWindowArea(position.x, position.y, BALL_SIZE * SGameEngine::GLOBAL_SCALE - 1, BALL_SIZE * SGameEngine::GLOBAL_SCALE - 1, EngineRenderer.RedrawBallRect, EngineRenderer.RedrawPrevBallRect, true);
//}
//
//void Border::RedrawBorders()
//{
//    EngineRenderer.RedrawWindowArea(LEVEL_BORDER_X_OFFSET, LEVEL_BORDER_Y_OFFSET, LEVEL_BORDER_TILE_WIDTH, LEVEL_BORDER_TILE_HEIGHT, EngineRenderer.RedrawBordersRect, EngineRenderer.RedrawPrevBordersRect);
//}

void Ball::MoveBall(Ball &ball)
{
    int nextBallXPosition, nextBallYPosition, 
        maxXPosition = Level::LEVEL_MAX_X_POSITION - BALL_SIZE, platformYPosition = Platform::PLATFORM_DEFAULT_Y_POSITION - BALL_SIZE;

    nextBallXPosition = ball.position.x + (int)(ball.speed * cos(ball.direction));
    nextBallYPosition = ball.position.y - (int)(ball.speed * sin(ball.direction));

    if (nextBallXPosition < Border::BORDER_X_OFFSET)
    {
        nextBallXPosition = Border::BORDER_X_OFFSET - (nextBallXPosition - Border::BORDER_X_OFFSET);
        ball.direction = M_PI - ball.direction;
    }

    if (nextBallYPosition < Border::BORDER_Y_OFFSET)
    {
        nextBallYPosition = Border::BORDER_Y_OFFSET - (nextBallYPosition - Border::BORDER_Y_OFFSET);
        ball.direction = -ball.direction;
    }

    if (nextBallXPosition > maxXPosition)
    {
        nextBallXPosition = maxXPosition - (nextBallXPosition - maxXPosition);
        ball.direction = M_PI - ball.direction;
    }

    if (nextBallYPosition > Level::LEVEL_MAX_Y_POSITION)
    {
        nextBallYPosition = Level::LEVEL_MAX_Y_POSITION - (nextBallYPosition - Level::LEVEL_MAX_Y_POSITION);
        ball.direction = M_PI + (M_PI - ball.direction);
    }

    if (nextBallYPosition > platformYPosition)
    {
        if (nextBallXPosition >= ObjectPlatform.position.x && nextBallXPosition <= ObjectPlatform.position.x + ObjectPlatform.width)
        {
            nextBallYPosition = platformYPosition - (nextBallYPosition - platformYPosition);
            ball.direction = M_PI + (M_PI - ball.direction);
        }
    }

    ObjectLevel.CheckLevelBrickHit(nextBallYPosition);
        
    ball.position.x = nextBallXPosition;
    ball.position.y = nextBallYPosition;

    EngineRenderer.RedrawGameObject(ball);
}

void SRenderer::CreateLevelBorder(HDC hDC, Vector2 position, bool is_horizontal_line)
{
    if (is_horizontal_line)
    {
        CreateRect(hDC, position.x, position.y, position.x + Border::BORDER_TILE_WIDTH, position.y + Border::BORDER_TILE_HEIGHT, EngineRenderer.LevelBorderFirstPen, EngineRenderer.LevelBorderFirstBrush, true);
        CreateRect(hDC, position.x, position.y, position.x + Border::BORDER_TILE_WIDTH, position.y + 1, EngineRenderer.LevelBorderSecondPen, EngineRenderer.LevelBorderSecondBrush, true);
        CreateRect(hDC, position.x + Border::BORDER_TILE_WIDTH / 2, position.y + Border::BORDER_TILE_HEIGHT / 2, position.x + Border::BORDER_TILE_WIDTH / 2 + 1, position.y + Border::BORDER_TILE_HEIGHT / 2 + 1, LevelBorderThirdPen, LevelBorderThirdBrush, true);
    }
    else
    {
        CreateRect(hDC, position.x, position.y, position.x + Border::BORDER_TILE_WIDTH, position.y + Border::BORDER_TILE_HEIGHT, EngineRenderer.LevelBorderFirstPen, EngineRenderer.LevelBorderFirstBrush, true);
        CreateRect(hDC, position.x, position.y, position.x + 1, position.y + Border::BORDER_TILE_HEIGHT, EngineRenderer.LevelBorderSecondPen, EngineRenderer.LevelBorderSecondBrush, true);
        CreateRect(hDC, position.x + Border::BORDER_TILE_WIDTH / 2, position.y + Border::BORDER_TILE_HEIGHT / 2, position.x + Border::BORDER_TILE_WIDTH / 2 + 1, position.y + Border::BORDER_TILE_HEIGHT / 2 - 1, LevelBorderThirdPen, LevelBorderThirdBrush, true);
    }
}

void SRenderer::CreateBounds(HDC hDC)
{
    // right border
    for (int i = 0; i < (Level::LEVEL_MAX_Y_POSITION * SGameEngine::GLOBAL_SCALE) / (Border::BORDER_TILE_HEIGHT * SGameEngine::GLOBAL_SCALE) + Border::BORDER_TOP_MARGIN + 2; i++)
        CreateLevelBorder(hDC, Vector2(Level::LEVEL_MAX_X_POSITION + Border::BORDER_RIGHT_MARGIN, i * Border::BORDER_TILE_HEIGHT + Border::BORDER_TOP_MARGIN), false);

    // left border
    for (int i = 0; i < (Level::LEVEL_MAX_Y_POSITION * SGameEngine::GLOBAL_SCALE) / (Border::BORDER_TILE_HEIGHT * SGameEngine::GLOBAL_SCALE) + Border::BORDER_TOP_MARGIN + 2; i++)
        CreateLevelBorder(hDC, Vector2(Border::BORDER_LEFT_MARGIN, i * Border::BORDER_TILE_HEIGHT + Border::BORDER_TOP_MARGIN), false);

    // top border
    for (int i = 0; i < ((Level::LEVEL_MAX_X_POSITION - Border::BORDER_TILE_WIDTH) * SGameEngine::GLOBAL_SCALE) / (Border::BORDER_TILE_WIDTH * SGameEngine::GLOBAL_SCALE) + Border::BORDER_LEFT_MARGIN - 1; i++)
        CreateLevelBorder(hDC, Vector2(i * Border::BORDER_TILE_WIDTH + Border::BORDER_LEFT_MARGIN + 1, 0), true);

    // bottom border
   /* for (int i = 0; i < (LEVEL_MAX_X_POSITION * GLOBAL_SCALE) / (LEVEL_BORDER_TILE_WIDTH * GLOBAL_SCALE) + LEVEL_BORDER_LEFT_MARGIN - 1; i++)
        CreateLevelBorder(hDC, i * LEVEL_BORDER_TILE_WIDTH + LEVEL_BORDER_LEFT_MARGIN + 1, LEVEL_MAX_Y_POSITION, true);*/

}

void Level::CheckLevelBrickHit(int &nextBallYPosition) const
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
                ObjectBall.direction = -ObjectBall.direction;
            }
        }
        brickYPosition -= CELL_HEIGHT;
    }
}