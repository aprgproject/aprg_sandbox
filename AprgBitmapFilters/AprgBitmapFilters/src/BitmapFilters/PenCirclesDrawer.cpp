#include "PenCirclesDrawer.hpp"

#include <BitmapFilters/Utilities.hpp>
#include <Dimensionless/Angle.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <cmath>

using namespace alba::Dimensionless;
using namespace alba::TwoDimensions;
using namespace alba::TwoDimensions::twoDimensionsHelper;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

PenCirclesDrawer::PenCirclesDrawer(
        PenCircles const& penCircles,
        BitmapSnippet & snippet)
    : m_penCircles(penCircles)
    , m_snippet(snippet)
    , m_snippetTraversal(snippet)
{}

void PenCirclesDrawer::drawCircles()
{
    for(PenCircles::PointPenCircleDetailsPair const& pair : m_penCircles.getPenCircles())
    {
        BitmapXY const& centerPoint(pair.first);
        Circle penCircle(convertBitmapXYToPoint(centerPoint), pair.second.radius);
        m_snippetTraversal.traverseCircleArea(penCircle, [&](BitmapXY const& pointInPenCircle)
        {
            m_snippet.setPixelAt(pointInPenCircle, pair.second.color);
        });
    }
}

void PenCirclesDrawer::drawCircleConnections()
{
    for(PenCircles::CircleCenterConnection const& connection : m_penCircles.getCenterConnections())
    {
        Point centerPoint1(convertBitmapXYToPoint(connection.first));
        Point centerPoint2(convertBitmapXYToPoint(connection.second));
        PenCircles::PenCircleDetails details1(m_penCircles.getPenCircleDetails(connection.first));
        PenCircles::PenCircleDetails details2(m_penCircles.getPenCircleDetails(connection.second));
        Circle circle1(centerPoint1, details1.radius);
        Circle circle2(centerPoint2, details2.radius);
        if(circle2.getRadius() > circle1.getRadius())
        {
            swap(circle1, circle2);
            swap(centerPoint1, centerPoint2);
            swap(details1, details2);
        }

        Point referenceDelta(centerPoint2-centerPoint1);
        Angle referenceAngle(getAngleBasedOnAPointAndOrigin(referenceDelta));
        double radiusDifference = circle1.getRadius() - circle2.getRadius();
        double distanceOfCenters = getDistance(centerPoint1, centerPoint2);
        Angle deltaAngle(AngleUnitType::Radians, acos(radiusDifference/distanceOfCenters));
        Angle angle1(referenceAngle+deltaAngle);
        Angle angle2(referenceAngle-deltaAngle);
        Point tangentPoint1InCircle1(circle1.getPointAtAngle(angle1.getRadians()));
        Point tangentPoint2InCircle1(circle1.getPointAtAngle(angle2.getRadians()));
        Point tangentPoint1InCircle2(circle2.getPointAtAngle(angle1.getRadians()));
        Point tangentPoint2InCircle2(circle2.getPointAtAngle(angle2.getRadians()));

        Quadrilateral quadrilateral(tangentPoint1InCircle1, tangentPoint2InCircle1, tangentPoint1InCircle2, tangentPoint2InCircle2);

        m_snippetTraversal.traverseQuadrilateralArea(
                    quadrilateral,
                    [&](BitmapXY const& point)
        {
            m_snippet.setPixelAt(point, details1.color);
        });

    }
}


}

}
