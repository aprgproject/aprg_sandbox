#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <Common/Optional/AlbaOptional.hpp>

namespace alba
{
namespace AprgBitmap
{
class OutwardSnakeLikeTraversal
{
public:
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };
    OutwardSnakeLikeTraversal(
            BitmapXY const& currentPoint,
            Direction const direction,
            unsigned int const lowestLeft,
            unsigned int const highestRight,
            unsigned int const lowestTop,
            unsigned int const highestBottom);

    bool isTraversalFinished() const;
    BitmapXY getNextPoint();

private:
    BitmapXY fixPoint(BitmapXY const& point);
    void gotoNextPoint();
    void move();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void switchDirection();
    void performScheduledTeleport();
    void teleportToNextOfMostLeftAndSwitchDirection();
    void teleportToNextOfMostRightAndSwitchDirection();
    void teleportToNextOfMostTopAndSwitchDirection();
    void teleportToNextOfMostBottomAndSwitchDirection();
    bool isPointInCorner() const;
    bool cannotTeleport() const;
    BitmapXY m_currentPoint;
    Direction m_direction;
    AlbaOptional<Direction> m_scheduledTeleportDirection;
    AlbaOptional<Direction> m_previousMovementDirection;
    unsigned int m_lowestLeft;
    unsigned int m_highestRight;
    unsigned int m_lowestTop;
    unsigned int m_highestBottom;
    unsigned int m_lastMostLeft;
    unsigned int m_lastMostRight;
    unsigned int m_lastMostTop;
    unsigned int m_lastMostBottom;
    bool m_isStart;
    bool m_isFinished;
};

}

}
