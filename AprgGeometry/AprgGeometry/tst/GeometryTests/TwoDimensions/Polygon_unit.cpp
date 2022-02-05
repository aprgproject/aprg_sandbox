#include <Geometry/TwoDimensions/Polygon.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

namespace TwoDimensions
{

TEST(PolygonTest, PolygonCanBeCreated)
{
    Polygon<3> polygon{Point(1,1), Point(2,3), Point(0,17)};
}

}

}
