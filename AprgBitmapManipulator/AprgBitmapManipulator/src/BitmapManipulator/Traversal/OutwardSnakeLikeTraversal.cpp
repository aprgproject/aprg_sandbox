#include "OutwardSnakeLikeTraversal.hpp"

#include <Common/Math/Helpers/ComputationHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

OutwardSnakeLikeTraversal::OutwardSnakeLikeTraversal(
        BitmapXY const& currentPoint,
        Direction const direction,
        unsigned int const lowestLeft,
        unsigned int const highestRight,
        unsigned int const lowestTop,
        unsigned int const highestBottom)
    : m_currentPoint()
    , m_direction(direction)
    , m_lowestLeft(lowestLeft)
    , m_highestRight(highestRight)
    , m_lowestTop(lowestTop)
    , m_highestBottom(highestBottom)
    , m_lastMostLeft(currentPoint.getX())
    , m_lastMostRight(currentPoint.getX())
    , m_lastMostTop(currentPoint.getY())
    , m_lastMostBottom(currentPoint.getY())
    , m_isStart(true)
    , m_isFinished(false)
{
    m_currentPoint = fixPoint(currentPoint);
    m_lastMostLeft = m_currentPoint.getX();
    m_lastMostRight = m_currentPoint.getX();
    m_lastMostTop = m_currentPoint.getY();
    m_lastMostBottom = m_currentPoint.getY();
}

BitmapXY OutwardSnakeLikeTraversal::fixPoint(
        BitmapXY const& point)
{
    BitmapXY newPoint(point);
    newPoint.setX(clampLowerBound(newPoint.getX(), m_lowestLeft));
    newPoint.setX(clampHigherBound(newPoint.getX(), m_highestRight));
    newPoint.setY(clampLowerBound(newPoint.getY(), m_lowestTop));
    newPoint.setY(clampHigherBound(newPoint.getY(), m_highestBottom));
    return newPoint;
}

bool OutwardSnakeLikeTraversal::isTraversalFinished() const
{
    return m_isFinished;
}

BitmapXY OutwardSnakeLikeTraversal::getNextPoint()
{
    BitmapXY result(m_currentPoint);
    gotoNextPoint();
    return result;
}

void OutwardSnakeLikeTraversal::gotoNextPoint()
{
    if(!m_isFinished)
    {
        if(m_scheduledTeleportDirection)
        {
            performScheduledTeleport();
        }        else
        {
            move();
        }    }
    m_isStart=false;
}

void OutwardSnakeLikeTraversal::move()
{
    switch(m_direction)
    {
    case Direction::Left:
        moveLeft();
        break;
    case Direction::Right:
        moveRight();
        break;
    case Direction::Up:
        moveUp();
        break;
    case Direction::Down:
        moveDown();
        break;
    }
}

void OutwardSnakeLikeTraversal::moveLeft()
{
    unsigned int x = m_currentPoint.getX();
    if(m_lowestLeft < x)
    {
        x=x-1;
        m_currentPoint.setX(x);
        m_previousMovementDirection = Direction::Left;
    }
    if(x < m_lastMostLeft)
    {        m_lastMostLeft = x;
        switchDirection();
    }
    else if(m_lowestLeft == x)
    {
        if(m_previousMovementDirection
                && m_previousMovementDirection.value() == Direction::Left)
        {
            m_scheduledTeleportDirection = Direction::Down;
        }
        else
        {            teleportToNextOfMostBottomAndSwitchDirection();
        }
    }
}
void OutwardSnakeLikeTraversal::moveRight()
{
    unsigned int x = m_currentPoint.getX();
    if(x < m_highestRight)
    {
        x=x+1;
        m_currentPoint.setX(x);
        m_previousMovementDirection = Direction::Right;
    }
    if(m_lastMostRight < x)
    {        m_lastMostRight = x;
        switchDirection();
    }
    else if(m_highestRight == x)
    {
        if(m_previousMovementDirection
                && m_previousMovementDirection.value() == Direction::Right)
        {
            m_scheduledTeleportDirection = Direction::Up;
        }
        else
        {            teleportToNextOfMostTopAndSwitchDirection();
        }
    }
}
void OutwardSnakeLikeTraversal::moveUp()
{
    unsigned int y = m_currentPoint.getY();
    if(m_lowestTop < y)
    {
        y=y-1;
        m_currentPoint.setY(y);
        m_previousMovementDirection = Direction::Up;
    }
    if(y < m_lastMostTop)
    {        m_lastMostTop = y;
        switchDirection();
    }
    else if(m_lowestTop == y)
    {
        if(m_previousMovementDirection
                && m_previousMovementDirection.value() == Direction::Up)
        {
            m_scheduledTeleportDirection = Direction::Left;
        }
        else
        {            teleportToNextOfMostLeftAndSwitchDirection();
        }
    }
}
void OutwardSnakeLikeTraversal::moveDown()
{
    unsigned int y = m_currentPoint.getY();
    if(y < m_highestRight)
    {
        y=y+1;
        m_currentPoint.setY(y);
        m_previousMovementDirection = Direction::Down;
    }
    if(m_lastMostBottom < y)
    {        m_lastMostBottom = y;
        switchDirection();
    }
    else if(m_highestBottom == y)
    {
        if(m_previousMovementDirection
                && m_previousMovementDirection.value() == Direction::Down)
        {
            m_scheduledTeleportDirection = Direction::Right;
        }
        else
        {            teleportToNextOfMostRightAndSwitchDirection();
        }
    }
}
void OutwardSnakeLikeTraversal::switchDirection()
{
    switch(m_direction)
    {
    case Direction::Left:
        m_direction = Direction::Down;
        break;
    case Direction::Right:
        m_direction = Direction::Up;
        break;
    case Direction::Up:
        m_direction = Direction::Left;
        break;
    case Direction::Down:
        m_direction = Direction::Right;
        break;
    }
}

void OutwardSnakeLikeTraversal::performScheduledTeleport()
{
    switch(m_scheduledTeleportDirection.value())
    {
    case Direction::Left:
        teleportToNextOfMostLeftAndSwitchDirection();        break;
    case Direction::Right:
        teleportToNextOfMostRightAndSwitchDirection();
        break;    case Direction::Up:
        teleportToNextOfMostTopAndSwitchDirection();
        break;
    case Direction::Down:
        teleportToNextOfMostBottomAndSwitchDirection();
        break;
    }
    m_scheduledTeleportDirection.reset();
}

void OutwardSnakeLikeTraversal::teleportToNextOfMostLeftAndSwitchDirection(){
    if(cannotTeleport())
    {
        m_isFinished=true;    }
    else
    {
        if(m_lowestLeft<m_lastMostLeft)
        {
            m_lastMostLeft = m_lastMostLeft-1;
            m_currentPoint.setX(m_lastMostLeft);
            m_direction = Direction::Down;
        }
        else
        {
            m_currentPoint.setX(m_lastMostLeft);
            teleportToNextOfMostBottomAndSwitchDirection();
        }
        m_previousMovementDirection.reset();
    }
}
void OutwardSnakeLikeTraversal::teleportToNextOfMostRightAndSwitchDirection()
{
    if(cannotTeleport())    {
        m_isFinished=true;
    }
    else
    {
        if(m_lastMostRight<m_highestRight)
        {
            m_lastMostRight = m_lastMostRight+1;
            m_currentPoint.setX(m_lastMostRight);
            m_direction = Direction::Up;
        }
        else
        {
            m_currentPoint.setX(m_lastMostRight);
            teleportToNextOfMostTopAndSwitchDirection();
        }
        m_previousMovementDirection.reset();
    }
}
void OutwardSnakeLikeTraversal::teleportToNextOfMostTopAndSwitchDirection()
{
    if(cannotTeleport())    {
        m_isFinished=true;
    }
    else
    {
        if(m_lowestTop<m_lastMostTop)
        {
            m_lastMostTop = m_lastMostTop-1;
            m_currentPoint.setY(m_lastMostTop);
            m_direction = Direction::Left;
        }
        else
        {
            m_currentPoint.setY(m_lastMostTop);
            teleportToNextOfMostLeftAndSwitchDirection();
        }
        m_previousMovementDirection.reset();
    }
}
void OutwardSnakeLikeTraversal::teleportToNextOfMostBottomAndSwitchDirection()
{
    if(cannotTeleport())    {
        m_isFinished=true;
    }
    else
    {
        if(m_lastMostBottom<m_highestBottom)
        {
            m_lastMostBottom = m_lastMostBottom+1;
            m_currentPoint.setY(m_lastMostBottom);
            m_direction = Direction::Right;
        }
        else
        {
            m_currentPoint.setY(m_lastMostBottom);
            teleportToNextOfMostRightAndSwitchDirection();
        }
        m_previousMovementDirection.reset();
    }
}
bool OutwardSnakeLikeTraversal::isPointInCorner() const
{
    return (m_currentPoint.getX() == m_lowestLeft || m_currentPoint.getX() == m_highestRight)            && (m_currentPoint.getY() == m_lowestTop || m_currentPoint.getY() == m_highestBottom);
}

bool OutwardSnakeLikeTraversal::cannotTeleport() const
{
    return m_lowestLeft==m_lastMostLeft
            && m_highestRight==m_lastMostRight
            && m_lowestTop==m_lastMostTop
            && m_highestBottom==m_lastMostBottom;
}

}

}
