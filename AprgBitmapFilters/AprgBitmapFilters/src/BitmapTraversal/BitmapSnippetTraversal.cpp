#include "BitmapSnippetTraversal.hpp"

#include <BitmapFilters/Utilities.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::TwoDimensions;

namespace alba
{

namespace AprgBitmap
{

BitmapSnippetTraversal::BitmapSnippetTraversal(BitmapSnippet const& bitmapSnippet)
    : m_bitmapSnippet(bitmapSnippet)
{}

void BitmapSnippetTraversal::traverse(
        Circle const& circle,
        TraverseOperation const& traverseOperation) const
{
    circle.traverseArea(1, [&](Point const& point)
    {
        BitmapXY pointInCircle(convertPointToBitmapXY(point));
        checkPointBeforeDoingTraverseOperation(pointInCircle, traverseOperation);
    });
}

void BitmapSnippetTraversal::traverse(
        BitmapXY const& centerPoint,
        OutwardCircleTraversal::RadiusCoordinatesPair const& radiusCoordinatesPair,
        TraverseOperation const& traverseOperation) const
{
    unsigned int i = radiusCoordinatesPair.second.first;
    unsigned int j = radiusCoordinatesPair.second.second;
    if(i==0 && j==0)
    {
        checkPointBeforeDoingTraverseOperation(centerPoint, traverseOperation);
    }
    else if(i==0)
    {
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()+j, centerPoint.getY()), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()-j, centerPoint.getY()), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY()+j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY()-j), traverseOperation);
    }
    else if(j==0)
    {
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()+i, centerPoint.getY()), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()-i, centerPoint.getY()), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY()+i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX(), centerPoint.getY()-i), traverseOperation);
    }
    else if(i==j)
    {
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()+i, centerPoint.getY()+i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()-i, centerPoint.getY()+i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()+i, centerPoint.getY()-i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()-i, centerPoint.getY()-i), traverseOperation);
    }
    else
    {
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()+i, centerPoint.getY()+j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()-i, centerPoint.getY()+j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()+i, centerPoint.getY()-j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()-i, centerPoint.getY()-j), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()+j, centerPoint.getY()+i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()-j, centerPoint.getY()+i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()+j, centerPoint.getY()-i), traverseOperation);
        checkPointBeforeDoingTraverseOperation(BitmapXY(centerPoint.getX()-j, centerPoint.getY()-i), traverseOperation);
    }
}

void BitmapSnippetTraversal::checkPointBeforeDoingTraverseOperation(
        BitmapXY const& point,
        TraverseOperation const& traverseOperation) const
{
    if(m_bitmapSnippet.isPositionInsideTheSnippet(point))
    {
        traverseOperation(point);
    }
}

}

}
