#include "Platform.h"

Platform::Platform() : 
    StaticObject(Vector2(SConfig::PLATFORM_DEFAULT_X_POSITION, SConfig::PLATFORM_DEFAULT_Y_POSITION), PLATFORM_DEFAULT_WIDTH, PLATFORM_DEFAULT_HEIGHT), 
platformInnerWidth(PLATFORM_DEFAULT_INNER_WIDTH),
platformXStep(PLATFORM_DEFAULT_X_STEP)
{}

void Platform::MovePlatform(EKeyType keyType)
{
    if (keyType == EKT_RIGHT)
    {
        position.x += platformXStep * SConfig::GLOBAL_SCALE;
        if (position.x > SConfig::LEVEL_MAX_X_POSITION - width + 1)
            position.x = SConfig::LEVEL_MAX_X_POSITION - width + 1;
        this->RedrawGameObject();
    }
    else if(keyType == EKT_LEFT)
    {
        position.x -= platformXStep * SConfig::GLOBAL_SCALE;
        if (position.x < SConfig::BORDER_X_OFFSET)
            position.x = SConfig::BORDER_X_OFFSET;
        this->RedrawGameObject();
    }
}