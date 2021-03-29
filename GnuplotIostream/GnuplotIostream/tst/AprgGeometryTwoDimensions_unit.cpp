#include "gnuplot-iostream.h"

#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Hyperbola.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::TwoDimensions;
using namespace std;

void graphPoints(Points const& points, string const& nameOfGraph)
{
    Gnuplot gp;
    gp << "plot ";
    {
        vector<pair<double, double>> pts;
        for(unsigned int i=0; i<points.size(); i++)
        {
            pts.emplace_back(make_pair(points[i].getX(), points[i].getY()));
        }
        gp << gp.binFile1d(pts, "record") << "with lines title '"<< nameOfGraph <<"'";
    }
    gp << endl;
}


TEST(AprgGeometryTwoDimensionsTest, DISABLED_CircleAtOriginWithRadius)
{
    Circle circle(Point(0,0), 3);
    Points points(circle.getPointsForCircumference(0.001));
    graphPoints(points, "CircleAtOriginWithRadius");
}

TEST(HyperbolaTest, DISABLED_HyperbolaAtOriginWithRadius)
{
    Hyperbola hyperbola(Point(0, 0), 3, 2);
    Points points(hyperbola.getPointsForShape(0.001));
    graphPoints(points, "HyperbolaAtOriginWithRadius");
}
