#include "Brick.h"

void Brick::Act()
{
	if (fadeStep < BRICK_MAX_FADE_STEP)
	{
		EngineRenderer.CreatePenAndBrush(85 - fadeStep * 85 / BRICK_MAX_FADE_STEP, 255 - fadeStep * 255 / BRICK_MAX_FADE_STEP, 255 - fadeStep * 255 / BRICK_MAX_FADE_STEP, EngineRenderer.fadeColorPen, EngineRenderer.fadeColorBrush);
		fadeStep++;
		this->RedrawGameObject();
	}
}