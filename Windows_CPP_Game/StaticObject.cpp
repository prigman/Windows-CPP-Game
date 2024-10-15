#include "StaticObject.h"

StaticObject::StaticObject() : 
	GameObject()
{}

StaticObject::StaticObject(Vector2 position, int width, int height) : 
	GameObject(position, width, height)
{}
