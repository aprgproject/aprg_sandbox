#include <AprgGnuPlot/AprgGnuPlot3D.hpp>
#include <Geometry/ThreeDimensions/Constructs/Line.hpp>
#include <Geometry/ThreeDimensions/Constructs/Plane.hpp>
#include <Geometry/ThreeDimensions/Constructs/Point.hpp>
#include <Geometry/ThreeDimensions/Utilities/ThreeDimensionsUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::ThreeDimensions;
using namespace alba::ThreeDimensions::threeDimensionsUtilities;
using namespace std;

namespace alba{

TEST(AprgGeometryThreeDimensionsTest, DISABLED_LineWithSlope)
{    Line line(Point(0,0,0), Point(2,3,-4));
    AprgGnuPlot3D::PointsInGraph points;
    for(double x=-10; x<10; x+=0.1)
    {
        points.emplace_back(AprgGnuPlot3D::getPoint(x, line.calculateYFromX(x), line.calculateZFromX(x)));
    }

    AprgGnuPlot3D gnuPlot3D;
    gnuPlot3D.setTitle("Graph of line with slope", R"("font ",22")");
    gnuPlot3D.setXAxis("X", R"("font ",15")");
    gnuPlot3D.setYAxis("Y", R"("font ",15")");
    gnuPlot3D.setZAxis("Z", R"("font ",15")");
    gnuPlot3D.doGraphs([&]()
    {
        gnuPlot3D.graph(points, "LineWithSlope", "with lines linetype 1 linewidth 4");
    });
}

TEST(AprgGeometryThreeDimensionsTest, DISABLED_MultipleLinesAndPoints)
{
    Line line1(Point(5,-2,6), Point(1,1,1));
    Line line2(Point(1,1,1), Point(2,3,-4));
    Line line3(Point(5,-2,6), Point(2,3,-4));
    AprgGnuPlot3D::PointsInGraph points1;
    AprgGnuPlot3D::PointsInGraph points2;
    AprgGnuPlot3D::PointsInGraph points3;
    for(double x=-10; x<10; x+=0.1)
    {
        points1.emplace_back(AprgGnuPlot3D::getPoint(x, line1.calculateYFromX(x), line1.calculateZFromX(x)));
        points2.emplace_back(AprgGnuPlot3D::getPoint(x, line2.calculateYFromX(x), line2.calculateZFromX(x)));
        points3.emplace_back(AprgGnuPlot3D::getPoint(x, line3.calculateYFromX(x), line3.calculateZFromX(x)));
    }

    AprgGnuPlot3D gnuPlot3D;
    gnuPlot3D.setTitle("Graph with multiple lines and points", R"("font ",22")");
    gnuPlot3D.setXAxis("X", R"("font ",15")");
    gnuPlot3D.setYAxis("Y", R"("font ",15")");
    gnuPlot3D.setZAxis("Z", R"("font ",15")");
    gnuPlot3D.doGraphs([&]()
    {
        gnuPlot3D.graph(points1, "Line1", "with lines linetype 1 linewidth 4");
        gnuPlot3D.graph(points2, "Line2", "with lines linetype 2 linewidth 4");
        gnuPlot3D.graph(points3, "Line3", "with lines linetype 3 linewidth 4");
        gnuPlot3D.graph({AprgGnuPlot3D::getPoint(5,-2,6)}, "Point1", "with points pointsize 1 pointtype 1");
        gnuPlot3D.graph({AprgGnuPlot3D::getPoint(1,1,1)}, "Point2", "with points pointsize 1 pointtype 2");
        gnuPlot3D.graph({AprgGnuPlot3D::getPoint(2,3,-4)}, "Point3", "with points pointsize 1 pointtype 3");
    });
}

TEST(AprgGeometryThreeDimensionsTest, DISABLED_PlaneConstructedWithThreePoints)
{
    Point point1(1,0,1);
    Point point2(-2,0,2);
    Point point3(2,0,-1);
    Plane plane(point1, point2, point3);
    AprgGnuPlot3D::PointsInGraph planePoints;
    for(double x=-10; x<10; x+=0.5)
    {
        for(double z=-10; z<10; z+=0.5)
        {
            planePoints.emplace_back(AprgGnuPlot3D::getPoint(x, plane.calculateYFromXAndZ(x, z), z));
        }
    }

    AprgGnuPlot3D gnuPlot3D;
    gnuPlot3D.setTitle("Graph with plane", R"("font ",22")");
    gnuPlot3D.setXAxis("X", R"("font ",15")");
    gnuPlot3D.setYAxis("Y", R"("font ",15")");
    gnuPlot3D.setZAxis("Z", R"("font ",15")");
    gnuPlot3D.doGraphs([&]()
    {
        gnuPlot3D.graph(planePoints, "Plane", "with points palette pointsize 1 pointtype 1");
    });
}

TEST(AprgGeometryThreeDimensionsTest, DISABLED_LineOfIntersectionOfTwoPlanes)
{
    Point point1OfPlane1(1,0,0);
    Point point2OfPlane1(0,1,0);
    Point point3OfPlane1(0,0,1);
    Point point1OfPlane2(0,0,0);
    Point point2OfPlane2(1,1,1);
    Point point3OfPlane2(0,1,1);
    Plane plane1(point1OfPlane1, point2OfPlane1, point3OfPlane1);
    Plane plane2(point1OfPlane2, point2OfPlane2, point3OfPlane2);
    Line lineOfIntersection(getLineOfIntersectionOfTwoPlanes(plane1, plane2));
    AprgGnuPlot3D::PointsInGraph pointsOfPlane1;
    AprgGnuPlot3D::PointsInGraph pointsOfPlane2;
    AprgGnuPlot3D::PointsInGraph pointsOfLineOfIntersection;
    for(double x=-5; x<5; x+=0.5)
    {
        for(double z=-5; z<5; z+=0.5)
        {
            pointsOfPlane1.emplace_back(AprgGnuPlot3D::getPoint(x, plane1.calculateYFromXAndZ(x, z), z));
            pointsOfPlane2.emplace_back(AprgGnuPlot3D::getPoint(x, plane2.calculateYFromXAndZ(x, z), z));
        }
        pointsOfLineOfIntersection.emplace_back(
                    AprgGnuPlot3D::getPoint(x,lineOfIntersection.calculateYFromX(x).getConstReference(), lineOfIntersection.calculateZFromX(x).getConstReference()));
    }

    AprgGnuPlot3D gnuPlot3D;
    gnuPlot3D.setTitle("Line of intersection between two planes", R"("font ",22")");
    gnuPlot3D.setXAxis("X", R"("font ",15")");
    gnuPlot3D.setYAxis("Y", R"("font ",15")");
    gnuPlot3D.setZAxis("Z", R"("font ",15")");
    gnuPlot3D.doGraphs([&]()
    {
        gnuPlot3D.graph(pointsOfPlane1, "Plane1", "with points pointsize 1 pointtype 1");
        gnuPlot3D.graph(pointsOfPlane2, "Plane2", "with points pointsize 1 pointtype 2");
        gnuPlot3D.graph(pointsOfLineOfIntersection, "LineOfIntersection", "with lines linetype 1 linewidth 1");
        gnuPlot3D.graph({point1OfPlane1}, "Point1OfPlane1", "with points pointsize 1 pointtype 3");
        gnuPlot3D.graph({point2OfPlane1}, "Point2OfPlane1", "with points pointsize 1 pointtype 4");
        gnuPlot3D.graph({point3OfPlane1}, "Point3OfPlane1", "with points pointsize 1 pointtype 5");
        gnuPlot3D.graph({point1OfPlane2}, "Point1OfPlane2", "with points pointsize 1 pointtype 6");
        gnuPlot3D.graph({point2OfPlane2}, "Point2OfPlane2", "with points pointsize 1 pointtype 7");
        gnuPlot3D.graph({point3OfPlane2}, "Point3OfPlane2", "with points pointsize 1 pointtype 8");
    });
}

TEST(AprgGeometryThreeDimensionsTest, DISABLED_BrewersProblemForSimplexTest)
{
    Plane profitModel(13, 23, -1, 0); // 13A+23B=P
    Plane constraints1(1, 3, 0, -96); //A+3B<=96
    Plane constraints2(1, 1, 0, -40); //A+B<=40
    Plane constraints3(7, 4, 0, -238); //7A+4B<=238
    AprgGnuPlot3D::PointsInGraph profitPoints;
    AprgGnuPlot3D::PointsInGraph c1Points;
    AprgGnuPlot3D::PointsInGraph c2Points;
    AprgGnuPlot3D::PointsInGraph c3Points;
    for(double x=0; x<200; x+=2)
    {
        for(double y=0; y<200; y+=2)
        {
            if(x+3*y <= 96 && x+y <= 40 && 7*x+4*y <= 238) //A+3B<=96, A+B<=40, 7A+4B<=238
            {
                profitPoints.emplace_back(AprgGnuPlot3D::getPoint(x, y, profitModel.calculateZFromXAndY(x, y)));
            }
        }
    }
    for(double x=0; x<200; x+=5)
    {
        for(double z=0; z<1000; z+=20)
        {
            if(constraints1.calculateYFromXAndZ(x, z).getConstReference() > 0)
            {
                c1Points.emplace_back(AprgGnuPlot3D::getPoint(x, constraints1.calculateYFromXAndZ(x, z), z));
            }
            if(constraints2.calculateYFromXAndZ(x, z).getConstReference() > 0)
            {
                c2Points.emplace_back(AprgGnuPlot3D::getPoint(x, constraints2.calculateYFromXAndZ(x, z), z));
            }
            if(constraints3.calculateYFromXAndZ(x, z).getConstReference() > 0)
            {
                c3Points.emplace_back(AprgGnuPlot3D::getPoint(x, constraints3.calculateYFromXAndZ(x, z), z));
            }
        }
    }

    AprgGnuPlot3D gnuPlot3D;
    gnuPlot3D.setTitle("Graph of line with slope", R"("font ",22")");
    gnuPlot3D.setXAxis("X", R"("font ",15")");
    gnuPlot3D.setYAxis("Y", R"("font ",15")");
    gnuPlot3D.setZAxis("Z", R"("font ",15")");
    gnuPlot3D.doGraphs([&]()
    {
        gnuPlot3D.graph(profitPoints, "Profit", "with points palette pointsize 1 pointtype 1");
        gnuPlot3D.graph(c1Points, "Constraints 1", "with points pointsize 1 pointtype 2");
        gnuPlot3D.graph(c2Points, "Constraints 2", "with points pointsize 1 pointtype 3");
        gnuPlot3D.graph(c3Points, "Constraints 3", "with points pointsize 1 pointtype 4");
    });
}


}
