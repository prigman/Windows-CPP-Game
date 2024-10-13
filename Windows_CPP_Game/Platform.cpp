#include "Platform.h"


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