#include "Ball.h"

Ball::Ball() : 
    DynamicObject(Vector2(BALL_DEFAULT_X_POSITION, BALL_DEFAULT_Y_POSITION), SConfig::BALL_SIZE, SConfig::BALL_SIZE, 3.0, M_PI - M_PI_4) 
{}

void Ball::CheckLevelBrickHit(const char level[SConfig::LEVEL_MAX_ROWS][SConfig::LEVEL_MAX_BRICKS_IN_ROW], int &nextBallYPosition, double &direction) const
{
    int brickYPosition = SConfig::LEVEL_Y_OFFSET + SConfig::LEVEL_MAX_ROWS * SConfig::CELL_HEIGHT;

    for (int i = SConfig::LEVEL_MAX_ROWS - 1; i >= 0; i--)
    {
        for (int j = 0; j < SConfig::LEVEL_MAX_BRICKS_IN_ROW; j++)
        {
            if (level[i][j] == 0)
                continue;

            else if (nextBallYPosition < brickYPosition)
            {
                nextBallYPosition = brickYPosition - (nextBallYPosition - brickYPosition);
                direction = -direction;
            }
        }
        brickYPosition -= SConfig::CELL_HEIGHT;
    }
}

void Ball::MoveBall(const char level[SConfig::LEVEL_MAX_ROWS][SConfig::LEVEL_MAX_BRICKS_IN_ROW], Vector2 platformPosition, int platformWidth)
{
    int nextBallXPosition, nextBallYPosition, 
        maxXPosition = SConfig::LEVEL_MAX_X_POSITION - SConfig::BALL_SIZE, platformYPosition = SConfig::PLATFORM_DEFAULT_Y_POSITION - SConfig::BALL_SIZE;

    nextBallXPosition = position.x + (int)(speed * cos(direction));
    nextBallYPosition = position.y - (int)(speed * sin(direction));

    if (nextBallXPosition < SConfig::BORDER_X_OFFSET)
    {
        nextBallXPosition = SConfig::BORDER_X_OFFSET - (nextBallXPosition - SConfig::BORDER_X_OFFSET);
        direction = M_PI - direction;
    }

    if (nextBallYPosition < SConfig::BORDER_Y_OFFSET)
    {
        nextBallYPosition = SConfig::BORDER_Y_OFFSET - (nextBallYPosition - SConfig::BORDER_Y_OFFSET);
        direction = -direction;
    }

    if (nextBallXPosition > maxXPosition)
    {
        nextBallXPosition = maxXPosition - (nextBallXPosition - maxXPosition);
        direction = M_PI - direction;
    }

    if (nextBallYPosition > SConfig::LEVEL_MAX_Y_POSITION)
    {
        nextBallYPosition = SConfig::LEVEL_MAX_Y_POSITION - (nextBallYPosition - SConfig::LEVEL_MAX_Y_POSITION);
        direction = M_PI + (M_PI - direction);
    }

    if (nextBallYPosition > platformYPosition)
    {
        if (nextBallXPosition >= platformPosition.x && nextBallXPosition <= platformPosition.x + platformWidth)
        {
            nextBallYPosition = platformYPosition - (nextBallYPosition - platformYPosition);
            direction = M_PI + (M_PI - direction);
        }
    }

    this->CheckLevelBrickHit(level, nextBallYPosition, direction);

    position.x = nextBallXPosition;
    position.y = nextBallYPosition;

    this->RedrawGameObject(true);
}