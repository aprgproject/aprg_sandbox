#include "gnuplot-iostream.h"

#include <ThreeDimensions/Line.hpp>
#include <ThreeDimensions/Plane.hpp>
#include <ThreeDimensions/Point.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::ThreeDimensions;
using namespace std;

void graphPoints(Gnuplot & gp, Points const& points, string const& nameOfGraph)
{
    vector<pair<pair<double, double>, double>> pts;
    for(unsigned int i=0; i<points.size(); i++)
    {
        pts.emplace_back(make_pair(make_pair(points[i].getX(), points[i].getY()), points[i].getZ()));
    }
    gp << gp.binFile1d(pts, "record") << "with lines title '"<< nameOfGraph <<"'";
    gp << ", ";
}

void graphPoint(Gnuplot & gp, Point const& point, string const& nameOfGraph)
{
    vector<pair<pair<double, double>, double>> pts;
    pts.emplace_back(make_pair(make_pair(point.getX(), point.getY()), point.getZ()));
    gp << gp.binFile1d(pts, "record") << "with points palette pointsize 2 pointtype 2 title '"<< nameOfGraph <<"'";
    gp << ", ";
}


TEST(AprgGeometryThreeDimensionsTest, DISABLED_LineWithSlope)
{
    Gnuplot gp;
    gp << "splot ";
    Line line(Point(0,0,0), Point(2,3,-4));
    Points points;
    for(double x=-10; x<10; x+=0.1)
    {
        points.emplace_back(x, line.calculateYFromX(x), line.calculateZFromX(x));
    }
    graphPoints(gp, points, "LineWithSlope");
    gp << endl;
}

TEST(AprgGeometryThreeDimensionsTest, DISABLED_LineWithSlopeWithPoints)
{
    Gnuplot gp;
    //Gnuplot gp(stdout); //for debugging
    gp << "splot ";
    Line line1(Point(5,-2,6), Point(1,1,1));
    Line line2(Point(1,1,1), Point(2,3,-4));
    Line line3(Point(5,-2,6), Point(2,3,-4));
    //Line line3(Point(5,-2,6), Point(2,3,-4));
    Points points1;
    Points points2;
    Points points3;
    for(double x=-10; x<10; x+=0.1)
    {
        points1.emplace_back(x, line1.calculateYFromX(x), line1.calculateZFromX(x));
        points2.emplace_back(x, line2.calculateYFromX(x), line2.calculateZFromX(x));
        points3.emplace_back(x, line3.calculateYFromX(x), line3.calculateZFromX(x));
    }
    graphPoints(gp, points1, "Line1");
    graphPoints(gp, points2, "Line2");
    graphPoints(gp, points3, "Line3");
    graphPoint(gp, Point(5,-2,6), "Point1");
    graphPoint(gp, Point(1,1,1), "Point2");
    graphPoint(gp, Point(2,3,-4), "Point3");
    gp << endl;
    Plane plane(Point(5,-2,6), Point(1,1,1), Point(2,3,-4));
    //system("pause"); // for debugging
}

TEST(AprgGeometryThreeDimensionsTest, DISABLED_SamplePlane)
{
    Point point1(1,0,1);
    Point point2(-2,0,2);
    Point point3(2,0,-1);
    Gnuplot gp;
    gp << "splot ";
    Plane plane(point1, point2, point3);
    Points points;
    for(double x=-10; x<10; x+=1)
    {
        for(double z=-10; z<10; z+=1)
        {
            points.emplace_back(x, plane.calculateYFromXAndZ(x, z), z);
        }
    }
    graphPoints(gp, points, "SamplePlane");
    graphPoint(gp, point1, "Point1");
    graphPoint(gp, point2, "Point2");
    graphPoint(gp, point3, "Point3");
    gp << endl;
}