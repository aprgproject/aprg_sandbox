#include <Algorithm/SymbolTable/BinarySearchTree/Geometry/OrthogonalLineSegmentIntersectionSearch.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using SearchForTest = OrthogonalLineSegmentIntersectionSearch<unsigned int>;
}

TEST(OrthogonalLineSegmentIntersectionSearchTest, GetIntersectingPointsWorksWhenIntersectionIsAtTheMiddle)
{
    SearchForTest search;
    search.addHorizontalLine(3, 0, 5);
    search.addVerticalLine(3, 0, 5);

    auto pointsToVerify(search.getIntersectingPoints());

    SearchForTest::Points pointsToExpect{{3, 3}};
    EXPECT_EQ(pointsToExpect, pointsToVerify);
}

TEST(OrthogonalLineSegmentIntersectionSearchTest, GetIntersectingPointsWorksWhenIntersectionIsAtTheStartAndEnd)
{
    SearchForTest search;
    search.addHorizontalLine(3, 0, 5);
    search.addVerticalLine(0, 0, 5);
    search.addVerticalLine(5, 0, 5);

    auto pointsToVerify(search.getIntersectingPoints());

    SearchForTest::Points pointsToExpect{{0, 3}, {5, 3}};
    EXPECT_EQ(pointsToExpect, pointsToVerify);
}

TEST(OrthogonalLineSegmentIntersectionSearchTest, GetIntersectingPointsWorksOnComplicatedExample)
{
    SearchForTest search;
    search.addHorizontalLine(2, 1, 10);
    search.addHorizontalLine(4, 10, 13);
    search.addHorizontalLine(5, 2, 7);
    search.addHorizontalLine(5, 8, 14);
    search.addHorizontalLine(6, 3, 5);
    search.addHorizontalLine(7, 7, 12);
    search.addHorizontalLine(9, 4, 8);
    search.addHorizontalLine(10, 10, 13);
    search.addVerticalLine(6, 4, 8);
    search.addVerticalLine(9, 1, 3);
    search.addVerticalLine(11, 6, 11);
    search.addVerticalLine(14, 1, 11);

    auto pointsToVerify(search.getIntersectingPoints());

    SearchForTest::Points pointsToExpect{{6, 5}, {9, 2}, {11, 7}, {11, 10}, {14, 5}};
    EXPECT_EQ(pointsToExpect, pointsToVerify);
}

}

}
