#include "PenCirclesDrawer.hpp"

#include <BitmapFilters/Utilities.hpp>
#include <BitmapFilters/ColorUtilities.hpp>
#include <Dimensionless/Angle.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <cmath>
#include <set>

using namespace alba::AprgBitmap::ColorUtilities;
using namespace alba::Dimensionless;
using namespace alba::TwoDimensions;
using namespace alba::TwoDimensions::twoDimensionsHelper;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

PenCirclesDrawer::ColorDetails::ColorDetails()
    : totalRed(0)
    , totalGreen(0)
    , totalBlue(0)
    , totalWeight(0)
{}

bool PenCirclesDrawer::ColorDetails::isEmpty() const
{
    return totalWeight==0;
}

unsigned int PenCirclesDrawer::ColorDetails::getColor() const
{
    unsigned char red = static_cast<unsigned char>(round(totalRed/totalWeight));
    unsigned char green = static_cast<unsigned char>(round(totalGreen/totalWeight));
    unsigned char blue = static_cast<unsigned char>(round(totalBlue/totalWeight));
    return combineRgbToColor(red, green, blue);
}

void PenCirclesDrawer::ColorDetails::addColor(unsigned int const color, double const weight)
{
    totalRed+=extractRed(color)*weight;
    totalGreen+=extractGreen(color)*weight;
    totalBlue+=extractBlue(color)*weight;
    totalWeight+=weight;
}

void PenCirclesDrawer::ColorDetails::clear()
{
    totalRed=0;
    totalGreen=0;
    totalBlue=0;
    totalWeight=0;
}

PenCirclesDrawer::PenCirclesDrawer(
        PenCircles const& penCircles,
        BitmapSnippet & snippet)
    : m_snippet(snippet)
    , m_snippetTraversal(snippet)
    , m_penCircles(penCircles)
    , m_drawnPoints()
{}

void PenCirclesDrawer::draw()
{
    drawUsingCirclesWithOverlay();
}

void PenCirclesDrawer::drawUsingCirclesWithoutOverlay()
{
    writeCirclesWithoutOverlay();
}

void PenCirclesDrawer::drawUsingCirclesWithOverlay()
{
    writeCirclesWithOverlay();
}

void PenCirclesDrawer::drawUsingConnectedCircles()
{
    connectCirclesIfNeeded();
    putCircleConnectionsAndRemoveProcessedCircles();
    putCirclesWithOverlay();
    writeDrawnPointsInSnippet();
}

bool PenCirclesDrawer::isToBeConnected(
        PenCircles::PointPenCircleDetailsPair const& pair1,
        PenCircles::PointPenCircleDetailsPair const& pair2) const
{
    return isSimilar(pair1.second.color, pair2.second.color, 0x08)
            && getDistance(convertBitmapXYToPoint(pair1.first), convertBitmapXYToPoint(pair2.first))
            < (pair1.second.radius + pair2.second.radius);
}

void PenCirclesDrawer::writeDrawnPointsInSnippet()
{
    for(PointColorPair const& pointColorPair : m_drawnPoints)
    {
        m_snippet.setPixelAt(pointColorPair.first, pointColorPair.second);
    }
}

void PenCirclesDrawer::writeCirclesWithoutOverlay()
{
    for(PenCircles::PointPenCircleDetailsPair const& pair : m_penCircles.getPenCircles())
    {
        Circle penCircle(convertBitmapXYToPoint(pair.first), pair.second.radius);
        unsigned int circleColor(pair.second.color);
        m_snippetTraversal.traverseCircleArea(penCircle, [&](BitmapXY const& pointInCircle)
        {
            m_snippet.setPixelAt(pointInCircle, circleColor);
        });
    }
}

void PenCirclesDrawer::writeCirclesWithOverlay()
{
    PointToColorDetailsMap pointsWithColorDetails;
    for(PenCircles::PointPenCircleDetailsPair const& pair : m_penCircles.getPenCircles())
    {
        Circle penCircle(convertBitmapXYToPoint(pair.first), pair.second.radius);
        m_snippetTraversal.traverseCircleArea(penCircle, [&](BitmapXY const& pointInCircle)
        {
            pointsWithColorDetails[pointInCircle].addColor(pair.second.color, 1);
        });
    }
    for(PointColorDetailsPair const& pointAndColorDetails : pointsWithColorDetails)
    {
        ColorDetails colorDetails(pointAndColorDetails.second);
        BitmapXY const& pointInCircle(pointAndColorDetails.first);
        PointToColorMap::const_iterator it = m_drawnPoints.find(pointInCircle);
        if(it!=m_drawnPoints.cend())
        {
            colorDetails.addColor(it->second, 1);
        }
        m_snippet.setPixelAt(pointInCircle, colorDetails.getColor());
    }
}

void PenCirclesDrawer::connectCirclesIfNeeded()
{
    for(PenCircles::PointPenCircleDetailsPair const& mainPair : m_penCircles.getPenCircles())
    {
        BitmapXY const& centerPoint(mainPair.first);
        PenCircles::PointPenCircleDetailsPairs neighborPairs(m_penCircles.getNearestPenCirclesToAPoint(centerPoint, mainPair.second.radius));
        for(PenCircles::PointPenCircleDetailsPair const& neighborPair : neighborPairs)
        {
            if(mainPair.first!=neighborPair.first && isToBeConnected(mainPair, neighborPair))
            {
                m_penCircles.connectCircles(centerPoint, neighborPair.first);
            }
        }
    }
}

void PenCirclesDrawer::putCirclesWithoutOverlay()
{
    for(PenCircles::PointPenCircleDetailsPair const& pair : m_penCircles.getPenCircles())
    {
        Circle penCircle(convertBitmapXYToPoint(pair.first), pair.second.radius);
        unsigned int circleColor(pair.second.color);
        m_snippetTraversal.traverseCircleArea(penCircle, [&](BitmapXY const& pointInCircle)
        {
            m_drawnPoints.emplace(pointInCircle, circleColor);
        });
    }
}

void PenCirclesDrawer::putCirclesWithOverlay()
{
    PointToColorDetailsMap pointsWithColorDetails;
    for(PenCircles::PointPenCircleDetailsPair const& pair : m_penCircles.getPenCircles())
    {
        Circle penCircle(convertBitmapXYToPoint(pair.first), pair.second.radius);
        m_snippetTraversal.traverseCircleArea(penCircle, [&](BitmapXY const& pointInCircle)
        {
            pointsWithColorDetails[pointInCircle].addColor(pair.second.color, 1);
        });
    }
    for(PointColorDetailsPair const& pointAndColorDetails : pointsWithColorDetails)
    {
        ColorDetails colorDetails(pointAndColorDetails.second);
        BitmapXY const& pointInCircle(pointAndColorDetails.first);
        PointToColorMap::const_iterator it = m_drawnPoints.find(pointInCircle);
        if(it!=m_drawnPoints.cend())
        {
            colorDetails.addColor(it->second, 1);
        }
        m_drawnPoints.emplace(pointInCircle, colorDetails.getColor());
    }
}

void PenCirclesDrawer::putCircleConnectionsAndRemoveProcessedCircles()
{
    PointToColorDetailsMap pointsWithColorDetails;
    std::set<BitmapXY> centersOfFoundPenCircles;
    for(PenCircles::CircleCenterConnection const& connection : m_penCircles.getCenterConnections())
    {
        PointToColorMap connectionPoints;
        if(m_penCircles.isPenCircle(connection.first) && m_penCircles.isPenCircle(connection.second))
        {
            PenCircles::PenCircleDetails details1(m_penCircles.getPenCircleDetails(connection.first));
            PenCircles::PenCircleDetails details2(m_penCircles.getPenCircleDetails(connection.second));
            Point centerPoint1(convertBitmapXYToPoint(connection.first));
            Point centerPoint2(convertBitmapXYToPoint(connection.second));
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
            double ratioForArcCos = radiusDifference/distanceOfCenters;
            if(ratioForArcCos <= 1)
            {
                Angle deltaAngle(AngleUnitType::Radians, acos(ratioForArcCos));
                Angle angle1(referenceAngle+deltaAngle);
                Angle angle2(referenceAngle-deltaAngle);
                Point tangentPoint1InCircle1(circle1.getPointAtAngle(angle1.getRadians()));
                Point tangentPoint2InCircle1(circle1.getPointAtAngle(angle2.getRadians()));
                Point tangentPoint1InCircle2(circle2.getPointAtAngle(angle1.getRadians()));
                Point tangentPoint2InCircle2(circle2.getPointAtAngle(angle2.getRadians()));
                Line diameterInCircle1(tangentPoint1InCircle1, tangentPoint2InCircle1);
                Line diameterInCircle2(tangentPoint1InCircle2, tangentPoint2InCircle2);
                Line lineOfTwoCenters(centerPoint1, centerPoint2);
                Quadrilateral quadrilateral(tangentPoint1InCircle1, tangentPoint2InCircle1, tangentPoint1InCircle2, tangentPoint2InCircle2);

                m_snippetTraversal.traverseCircleArea(circle1, [&](BitmapXY const& pointInCircle)
                {
                    connectionPoints.emplace(pointInCircle, details1.color);
                });

                m_snippetTraversal.traverseCircleArea(circle2, [&](BitmapXY const& pointInCircle)
                {
                    connectionPoints.emplace(pointInCircle, details2.color);
                });

                m_snippetTraversal.traverseQuadrilateralArea(
                            quadrilateral, [&](BitmapXY const& pointInQuad)
                {
                    double weightForCircle1 = getDistance(diameterInCircle2, convertBitmapXYToPoint(pointInQuad));
                    double weightForCircle2 = getDistance(diameterInCircle1, convertBitmapXYToPoint(pointInQuad));
                    double sumOfWeights = weightForCircle1+weightForCircle2;
                    weightForCircle1 = weightForCircle1/sumOfWeights;
                    weightForCircle2 = weightForCircle2/sumOfWeights;
                    ColorDetails colorDetails;
                    colorDetails.addColor(details1.color, weightForCircle1);
                    colorDetails.addColor(details2.color, weightForCircle2);
                    connectionPoints[pointInQuad]=colorDetails.getColor();
                });
                for(PointColorPair const& pointColorPair : connectionPoints)
                {
                    /*double weight = (circle1.getRadius()-getDistance(lineOfTwoCenters, convertBitmapXYToPoint(pointColorPair.first)))/circle1.getRadius();
                    if(weight==0)
                    {
                        weight = static_cast<double>(1)/pow(circle1.getRadius(), 2);
                    }*/
                    pointsWithColorDetails[pointColorPair.first].addColor(pointColorPair.second, 1);
                }
                centersOfFoundPenCircles.emplace(connection.first);
                centersOfFoundPenCircles.emplace(connection.second);
            }
        }
    }
    for(BitmapXY const& centerOfFoundPenCircle : centersOfFoundPenCircles)
    {
        m_penCircles.removePenCircleAt(centerOfFoundPenCircle);
    }

    for(PointColorDetailsPair const& pointAndColorDetails : pointsWithColorDetails)
    {
        m_drawnPoints[pointAndColorDetails.first]=pointAndColorDetails.second.getColor();
    }
}


}

}
