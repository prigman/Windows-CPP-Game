#include "GameObject.h"

void GameObject::RedrawGameObject(bool isBallObject)
{
    EngineRenderer.RedrawWindowArea(position.x, position.y, width, height, redrawRect, redrawPrevRect, isBallObject, FALSE);
}
