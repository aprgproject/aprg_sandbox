#include <AprgGraph.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba;
using namespace std;

#define APRG_GRAPH_24_BIT_DEFAULT_FILE APRG_DIR R"(AprgGraph\AprgGraph\tst\Bitmaps\Default24Bit.bmp)"
#define APRG_GRAPH_24_BIT_GRAPH_OUTPUT_FILE APRG_DIR R"(AprgGraph\AprgGraph\tst\Bitmaps\GraphOutput.bmp)"

TEST(SampleTest, BitmapGraph24Bits)
{
    AlbaLocalPathHandler defaultFile(APRG_GRAPH_24_BIT_DEFAULT_FILE);
    AlbaLocalPathHandler graphOutputFile(APRG_GRAPH_24_BIT_GRAPH_OUTPUT_FILE);
    graphOutputFile.deleteFile();
    defaultFile.copyToNewFile(graphOutputFile.getFullPath());
    AprgGraph graph(graphOutputFile.getFullPath(), BitmapXY(800,450), BitmapDoubleXY(1, 1));
    graph.drawGrid(BitmapDoubleXY((double)1000/3, (double)1000/9));
    graph.drawLine(Line(1,1,1), 0x00FF0000);    graph.drawCircle(Circle(Point(0,0), 100), 0x000000FF);
    graph.drawFunctionUsingX(0x00FF00FF, [](double xValue)->double
    {
        return 100*sin(xValue/100);
    });
    graph.drawFunctionUsingY(0x00FF00FF, [](double yValue)->double
    {
        return 100*sin(yValue/100);
    });
    graph.saveChangesToBitmapFile();
}
