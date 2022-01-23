#include <AprgGnuPlot2D.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/Hyperbola.hpp>
#include <TwoDimensions/Line.hpp>#include <TwoDimensions/TwoDimensionsHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::TwoDimensions;
using namespace alba::TwoDimensions::twoDimensionsHelper;
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
    gnuPlot2D.startGraph();
    gnuPlot2D.graph(points, "CircleAtOriginWithRadius", "with lines linetype 2 linewidth 4");
    gnuPlot2D.endGraph();
}

TEST(AprgGeometryTwoDimensionsTest, DISABLED_HyperbolaAtOriginWithRadius)
{
    Hyperbola hyperbola(Point(0, 0), 3, 2);
    Points points(hyperbola.getPointsForShape(0.1));

    AprgGnuPlot2D gnuPlot2D;
    gnuPlot2D.setTitle("Hyperbola graph", R"("font ",22")");
    gnuPlot2D.setXAxis("X", R"("font ",15")");
    gnuPlot2D.setYAxis("Y", R"("font ",15")");
    gnuPlot2D.startGraph();
    gnuPlot2D.graph(points, "HyperbolaAtOriginWithRadius", "with points pointsize 1 pointtype 1");
    gnuPlot2D.endGraph();
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
    gnuPlot2D.startGraph();
    gnuPlot2D.graph(pointsCircle, "Circle", "with lines linetype 1 linewidth 1");
    gnuPlot2D.graph(pointsLine1, "Line1", "with lines linetype 2 linewidth 1");
    gnuPlot2D.graph(pointsLine2, "Line2", "with lines linetype 2 linewidth 1");
    gnuPlot2D.graph(pointsLine3, "Line3", "with lines linetype 2 linewidth 1");
    gnuPlot2D.endGraph();
}

}