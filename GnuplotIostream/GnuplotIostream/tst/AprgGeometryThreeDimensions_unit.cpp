#include "gnuplot-iostream.h"

#include <ThreeDimensions/Line.hpp>
#include <ThreeDimensions/Plane.hpp>
#include <ThreeDimensions/Point.hpp>

#include <gtest/gtest.h>

#include <cmath>


#include <Debug/AlbaDebug.hpp>

using namespace alba::ThreeDimensions;
using namespace std;

void graphPoints(Points const& points, string const& nameOfGraph)
{
    Gnuplot gp;
    gp << "splot ";
    {
        vector<pair<pair<double, double>, double>> pts;
        for(unsigned int i=0; i<points.size(); i++)
        {
            pts.emplace_back(make_pair(make_pair(points[i].getX(), points[i].getY()), points[i].getZ()));
        }
        gp << gp.binFile1d(pts, "record") << "with lines title '"<< nameOfGraph <<"'";
    }
    gp << endl;
}


TEST(AprgGeometryThreeDimensionsTest, DISABLED_LineWithSlope)
{
    Line line(Point(0,0,0), Point(2,3,-4));
    Points points;
    for(double x=-10; x<10; x+=0.1)
    {
        ALBA_PRINT3(x, line.calculateYFromX(x), line.calculateZFromX(x));
        points.emplace_back(x, line.calculateYFromX(x), line.calculateZFromX(x));
    }
    graphPoints(points, "LineWithSlope");
}

TEST(AprgGeometryThreeDimensionsTest, SamplePlane)
{
    Plane plane(Point(5,-2,6), Point(0,0,0), Point(2,3,-4));
    Points points;
    for(double x=-10; x<10; x+=0.1)
    {
        for(double y=-10; y<10; y+=0.1)
        {
            points.emplace_back(x, y, plane.calculateZFromXAndY(x, y));
        }
    }
    graphPoints(points, "SamplePlane");
}
