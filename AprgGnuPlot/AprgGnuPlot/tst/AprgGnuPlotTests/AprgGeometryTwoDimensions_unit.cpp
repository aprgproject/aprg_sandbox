#include <AprgGnuPlot/AprgGnuPlot2D.hpp>
#include <Geometry/TwoDimensions/Constructs/Circle.hpp>
#include <Geometry/TwoDimensions/Constructs/Hyperbola.hpp>
#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Utilities/TwoDimensionsUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::TwoDimensions;
using namespace alba::TwoDimensions::twoDimensionsUtilities;
using namespace std;

namespace alba
{

TEST(AprgGeometryTwoDimensionsTest, DISABLED_CircleAtOriginWithRadius)
{
    Circle circle(Point(0,0), 3);
    Points points(circle.getLocus(0.001));

    AprgGnuPlot2D gnuPlot2D;
    gnuPlot2D.setTitle("Circle graph", R"("font ",22")");
    gnuPlot2D.setXAxis("X", R"("font ",15")");
    gnuPlot2D.setYAxis("Y", R"("font ",15")");
    gnuPlot2D.doGraphs([&]()
    {
        gnuPlot2D.graph(points, "CircleAtOriginWithRadius", "with lines linetype 2 linewidth 4");
    });
}

TEST(AprgGeometryTwoDimensionsTest, DISABLED_HyperbolaAtOriginWithRadius)
{
    Hyperbola hyperbola(Point(0, 0), 3, 2);
    Points points(hyperbola.getPointsForShape(0.1));

    AprgGnuPlot2D gnuPlot2D;
    gnuPlot2D.setTitle("Hyperbola graph", R"("font ",22")");
    gnuPlot2D.setXAxis("X", R"("font ",15")");
    gnuPlot2D.setYAxis("Y", R"("font ",15")");
    gnuPlot2D.doGraphs([&]()
    {
        gnuPlot2D.graph(points, "HyperbolaAtOriginWithRadius", "with points pointsize 1 pointtype 1");
    });
}

TEST(AprgGeometryTwoDimensionsTest, DISABLED_MultipleGraphs)
{
    Circle circle(Point(1,2), 3);
    Line expectedLine1(getTangentLineAt(circle, Point(1,5)));
    Line expectedLine2(getTangentLineAt(circle, Point(4,2)));
    Line expectedLine3(getTangentLineAt(circle, Point(2.5,3.5)));
    Points pointsCircle(circle.getLocus(0.01));
    Points pointsLine1(expectedLine1.getPoints(Point(-10, -10), Point(10, 10), 0.001));
    Points pointsLine2(expectedLine2.getPoints(Point(-10, -10), Point(10, 10), 0.001));
    Points pointsLine3(expectedLine3.getPoints(Point(-10, -10), Point(10, 10), 0.001));

    AprgGnuPlot2D gnuPlot2D;
    gnuPlot2D.setTitle("Multiple graphs", R"("font ",22")");
    gnuPlot2D.setXAxis("X", R"("font ",15")");
    gnuPlot2D.setYAxis("Y", R"("font ",15")");
    gnuPlot2D.doGraphs([&]()
    {
        gnuPlot2D.graph(pointsCircle, "Circle", "with lines linetype 1 linewidth 1");
        gnuPlot2D.graph(pointsLine1, "Line1", "with lines linetype 2 linewidth 1");
        gnuPlot2D.graph(pointsLine2, "Line2", "with lines linetype 2 linewidth 1");
        gnuPlot2D.graph(pointsLine3, "Line3", "with lines linetype 2 linewidth 1");
    });
}

TEST(AprgGeometryTwoDimensionsTest, DISABLED_BrewersProblemForSimplexTest)
{
    Line constraints1(1, 3, -96); //A+3B<=96
    Line constraints2(1, 1, -40); //A+B<=40
    Line constraints3(7, 4, -238); //7A+4B<=238
    Points c1Points(constraints1.getPoints(Point(0, 0), Point(100, 100), 1));
    Points c2Points(constraints2.getPoints(Point(0, 0), Point(100, 100), 1));
    Points c3Points(constraints3.getPoints(Point(0, 0), Point(100, 100), 1));

    AprgGnuPlot2D gnuPlot2D;
    gnuPlot2D.setTitle("Multiple graphs", R"("font ",22")");
    gnuPlot2D.setXAxis("X", R"("font ",15")");
    gnuPlot2D.setYAxis("Y", R"("font ",15")");
    gnuPlot2D.doGraphs([&]()
    {
        gnuPlot2D.graph(c1Points, "Constraints 1", "with lines linetype 1 linewidth 1");
        gnuPlot2D.graph(c2Points, "Constraints 2", "with lines linetype 2 linewidth 1");
        gnuPlot2D.graph(c3Points, "Constraints 3", "with lines linetype 3 linewidth 1");
    });
}

}
