#include "Engine.h"

SGameEngine::SGameEngine() : 
    //hWnd(nullptr),
    firstColorPen(nullptr),
    secondColorPen(nullptr),
    whiteColorPen(nullptr),
    letterPen(nullptr),
    backgroundPen(nullptr),
    levelBorderFirstPen(nullptr),
    levelBorderSecondPen(nullptr),
    levelBorderThirdPen(nullptr),

    backgroundBrush(nullptr),
    firstColorBrush(nullptr),
    secondColorBrush(nullptr),
    whiteColorBrush(nullptr),
    levelBorderFirstBrush(nullptr),
    levelBorderSecondBrush(nullptr),
    levelBorderThirdBrush(nullptr)
{}

void SGameEngine::OnGameInitRedraw(HWND hWnd)
{
    EngineRenderer.hWnd = hWnd;

    EngineRenderer.SetPensAndBrushes();

    this->objectLevel.RedrawGameObject();
    this->objectPlatform.RedrawGameObject();
    this->objectBall.RedrawGameObject();
    this->objectBorder.RedrawGameObject();
}

void SGameEngine::InitGame(HWND hWnd)
{
    //hWnd = hWnd;
    SetTimer(hWnd, TIMER_ID, 1000 / SConfig::FRAMES_PER_SECOND, NULL);
    
    OnGameInitRedraw(hWnd);
}

int SGameEngine::OnTimer()
{
    objectBall.MoveBall(this->objectLevel.Level_01, this->objectPlatform.position, objectPlatform.width);
    objectBrick.Act();
    return 0;
}

int SGameEngine::OnKeyDown(EKeyType keyType)
{
    switch (keyType)
    {
    case EKT_LEFT:
    {
        objectPlatform.MovePlatform(EKT_LEFT);
        break;
    }
    case EKT_RIGHT:
    {
        objectPlatform.MovePlatform(EKT_RIGHT);
        break;
    }
    case EKT_SPACE:
    {
        break;
    }
    }
    return 0;
}