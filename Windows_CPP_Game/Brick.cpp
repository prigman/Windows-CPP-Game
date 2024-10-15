#include "Brick.h"

Brick::Brick() : 
	StaticObject(Vector2(SConfig::LEVEL_X_OFFSET, 100), SConfig::BRICK_WIDTH, SConfig::BRICK_HEIGHT), fadeStep(0)
{}

void Brick::Act()
{
	if (fadeStep < BRICK_MAX_FADE_STEP)
	{
		EngineRenderer.CreatePenAndBrush(85 - fadeStep * 85 / BRICK_MAX_FADE_STEP, 255 - fadeStep * 255 / BRICK_MAX_FADE_STEP, 255 - fadeStep * 255 / BRICK_MAX_FADE_STEP, EngineRenderer.fadeColorPen, EngineRenderer.fadeColorBrush);
		fadeStep++;
		this->RedrawGameObject();
	}
}