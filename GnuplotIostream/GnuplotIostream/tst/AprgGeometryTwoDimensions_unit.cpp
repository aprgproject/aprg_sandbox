#include "gnuplot-iostream.h"

#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Hyperbola.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::TwoDimensions;
using namespace alba::TwoDimensions::twoDimensionsHelper;
using namespace std;

namespace
{

void graphPoints(Gnuplot & gp, Points const& points, string const& nameOfGraph)
{
    vector<pair<double, double>> pts;
    for(unsigned int i=0; i<points.size(); i++)
    {
        pts.emplace_back(make_pair(points[i].getX(), points[i].getY()));
    }
    gp << gp.binFile1d(pts, "record") << "with lines title '"<< nameOfGraph <<"'";
    gp << ", ";
}

}


namespace alba
{

TEST(AprgGeometryTwoDimensionsTest, DISABLED_CircleAtOriginWithRadius)
{
    Gnuplot gp;
    gp << "plot ";
    Circle circle(Point(0,0), 3);
    Points points(circle.getLocus(0.001));
    graphPoints(gp, points, "CircleAtOriginWithRadius");
    gp << endl;
}

TEST(AprgGeometryTwoDimensionsTest, DISABLED_HyperbolaAtOriginWithRadius)
{
    Gnuplot gp;
    gp << "plot ";
    Hyperbola hyperbola(Point(0, 0), 3, 2);
    Points points(hyperbola.getPointsForShape(0.001));
    graphPoints(gp, points, "HyperbolaAtOriginWithRadius");
    gp << endl;
}

TEST(AprgGeometryTwoDimensionsTest, DISABLED_SampleCircle)
{
    Gnuplot gp;
    gp << "plot ";
    Circle circle(Point(1,2), 3);
    Line expectedLine1(getTangentLineAt(circle, Point(1,5)));
    Line expectedLine2(getTangentLineAt(circle, Point(4,2)));
    Line expectedLine3(getTangentLineAt(circle, Point(2.5,3.5)));

    Points pointsCircle(circle.getLocus(0.01));
    Points pointsLine1(expectedLine1.getPoints(Point(-10, -10), Point(10, 10), 0.001));
    Points pointsLine2(expectedLine2.getPoints(Point(-10, -10), Point(10, 10), 0.001));
    Points pointsLine3(expectedLine3.getPoints(Point(-10, -10), Point(10, 10), 0.001));
    graphPoints(gp, pointsCircle, "Circle");
    graphPoints(gp, pointsLine1, "Line1");
    graphPoints(gp, pointsLine2, "Line2");
    graphPoints(gp, pointsLine3, "Line3");
    gp << endl;
}

}
