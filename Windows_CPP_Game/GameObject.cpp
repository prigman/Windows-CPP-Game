#include "GameObject.h"

GameObject::GameObject() :
    position(0,0), width(0), height(0), redrawRect{0, 0, 0, 0}, redrawPrevRect{0, 0, 0, 0}
{}

GameObject::GameObject(Vector2 position, int width, int height) : 
    position(position), width(width), height(height), redrawRect{0, 0, 0, 0}, redrawPrevRect{0, 0, 0, 0} 
{}

void GameObject::RedrawGameObject(bool isBallObject)
{
    EngineRenderer.RedrawWindowArea(position.x, position.y, width, height, redrawRect, redrawPrevRect, isBallObject, FALSE);
}
