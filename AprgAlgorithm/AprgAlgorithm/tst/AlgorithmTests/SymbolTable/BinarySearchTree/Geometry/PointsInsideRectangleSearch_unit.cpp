#include <Algorithm/SymbolTable/BinarySearchTree/Geometry/PointsInsideRectangleSearch.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using SearchForTest = PointsInsideRectangleSearch<double>;
}

TEST(PointsInsideRectangleSearchTest, GetPointsInsideTheRectangleWorksWhenRectangleIsAtTheLeft)
{
    SearchForTest search({-7, -2}, {-3, 2});
    search.addPoint({0, 0});
    search.addPoint({-5, 0});
    search.addPoint({5, 0});

    auto pointsToVerify(search.getPointsInsideTheRectangle());

    SearchForTest::Points pointsToExpect{{-5, 0}};
    EXPECT_EQ(pointsToExpect, pointsToVerify);
}

TEST(PointsInsideRectangleSearchTest, GetPointsInsideTheRectangleWorksWhenRectangleIsAtTheRight)
{
    SearchForTest search({3, -2}, {7, 2});
    search.addPoint({0, 0});
    search.addPoint({-5, 0});
    search.addPoint({5, 0});

    auto pointsToVerify(search.getPointsInsideTheRectangle());

    SearchForTest::Points pointsToExpect{{5, 0}};
    EXPECT_EQ(pointsToExpect, pointsToVerify);
}

TEST(PointsInsideRectangleSearchTest, GetPointsInsideTheRectangleWorksWhenRectangleIsAtTheLeftAndRight)
{
    SearchForTest search({-7, -2}, {7, 2});
    search.addPoint({0, 0});
    search.addPoint({-5, 0});
    search.addPoint({5, 0});

    auto pointsToVerify(search.getPointsInsideTheRectangle());

    SearchForTest::Points pointsToExpect{{0, 0}, {-5, 0}, {5, 0}};
    EXPECT_EQ(pointsToExpect, pointsToVerify);
}

TEST(PointsInsideRectangleSearchTest, GetPointsInsideTheRectangleWorksOnComplicatedExample)
{
    SearchForTest search({-4.5, -0.5}, {-1.5, 2.5});
    search.addPoint({0, 0});
    search.addPoint({3, -2});
    search.addPoint({-2, 2});
    search.addPoint({-3, -4});
    search.addPoint({-4, 0});
    search.addPoint({-1, 3});
    search.addPoint({1, -3});
    search.addPoint({7, 5});
    search.addPoint({6, 3});
    search.addPoint({2, -4});

    auto pointsToVerify(search.getPointsInsideTheRectangle());

    SearchForTest::Points pointsToExpect{{-2, 2}, {-4, 0}};
    EXPECT_EQ(pointsToExpect, pointsToVerify);
}

}

}
