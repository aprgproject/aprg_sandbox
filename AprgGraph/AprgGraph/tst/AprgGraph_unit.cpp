#include <AprgGraph.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::algebra;
using namespace alba::AprgBitmap;
using namespace alba::TwoDimensions;
using namespace std;
#define APRG_GRAPH_24_BIT_DEFAULT_FILE APRG_DIR R"(AprgGraph\AprgGraph\tst\Bitmaps\Default24Bit.bmp)"
#define APRG_GRAPH_24_BIT_GRAPH_OUTPUT_FILE APRG_DIR R"(AprgGraph\AprgGraph\tst\Bitmaps\GraphOutput.bmp)"
namespace alba
{

TEST(SampleTest, BitmapGraph24Bits)
{
    AlbaLocalPathHandler defaultFile(APRG_GRAPH_24_BIT_DEFAULT_FILE);
    AlbaLocalPathHandler graphOutputFile(APRG_GRAPH_24_BIT_GRAPH_OUTPUT_FILE);
    graphOutputFile.deleteFile();
    defaultFile.copyToNewFile(graphOutputFile.getFullPath());

    AprgGraph graph(graphOutputFile.getFullPath(), BitmapXY(800,450), BitmapDoubleXY(50, 50));
    graph.drawGrid(BitmapDoubleXY((double)5, (double)5));
    graph.drawLine(Line(1,1,1), 0x00FF0000);
    graph.drawCircle(Circle(Point(0,0), 100), 0x000000FF);
    graph.drawEllipse(Ellipse(Point(0,0), 300, 200), 0x0000FFFF);
    graph.drawHyperbola(Hyperbola(Point(0,0), 200, 150), 0x0000FFFF);

    Term polynomialTermInX(Polynomial{Monomial(1, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(-7, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(10, {})});
    Term polynomialTermInY(Polynomial{Monomial(1, {{"y", 4}}), Monomial(-1, {{"y", 3}}), Monomial(-1, {{"y", 2}}), Monomial(-2, {{"y", 1}}), Monomial(-6, {})});
    graph.drawTermWithXYSubstitution(polynomialTermInX, 0x0000A1BA);
    graph.drawTermWithXYSubstitution(polynomialTermInY, 0x00A1BA00);

    Polynomial leftPolynomial1{Monomial(1, {{"x", 1}, {"y", 1}}), Monomial(-1, {{"x", 2}}), Monomial(1, {})};
    Polynomial leftPolynomial2{Monomial(1, {{"x", 2}}), Monomial(-2, {{"x", 1}, {"y", 1}}), Monomial(1, {{"y", 2}}), Monomial(2, {{"x", 1}}), Monomial(-3, {{"y", 1}}), Monomial(2, {})};
    Equation equation1(Term(leftPolynomial1), "=", Term(AlbaNumber(0)));
    Equation equation2(Term(leftPolynomial2), "=", Term(AlbaNumber(0)));
    graph.drawEquationWithXYSubstitution(equation1, 0x0000A1BA);
    graph.drawEquationWithXYSubstitution(equation2, 0x00A1BA00);

    graph.drawFunctionUsingX(0x00FF00FF, [](double xValue)->double
    {
        return 100*sin(xValue/100);    });
    graph.drawFunctionUsingY(0x00FF00FF, [](double yValue)->double
    {
        return 100*sin(yValue/100);    });
    graph.saveChangesToBitmapFile();
}

}
