#include <Algorithm/SymbolTable/BinarySearchTree/Geometry/NearestPointSearch.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using SearchForTest = NearestPointSearch<double>;
}

TEST(NearestPointSearchTest, GetNearestPointWorksWhenPointIsAtTheLeft)
{
    SearchForTest search;
    search.addPoint({0, 0});
    search.addPoint({-5, 0});
    search.addPoint({5, 0});

    auto pointToVerify(search.getNearestPoint({-3, 0}));
    SearchForTest::Point pointToExpect{-5, 0};
    EXPECT_EQ(pointToExpect, pointToVerify);
}

TEST(NearestPointSearchTest, GetNearestPointWorksWhenPointIsAtTheRight)
{
    SearchForTest search;
    search.addPoint({0, 0});
    search.addPoint({-5, 0});
    search.addPoint({5, 0});

    auto pointToVerify(search.getNearestPoint({3, 0}));
    SearchForTest::Point pointToExpect{5, 0};
    EXPECT_EQ(pointToExpect, pointToVerify);
}

TEST(NearestPointSearchTest, GetNearestPointWorksOnComplicatedExample)
{
    SearchForTest search;
    search.addPoint({0, 0});
    search.addPoint({3, -2});
    search.addPoint({-2, 2});
    search.addPoint({-3, -4});
    search.addPoint({-4, 0});    search.addPoint({-1, 3});
    search.addPoint({1, -3});
    search.addPoint({7, 5});
    search.addPoint({6, 3});
    search.addPoint({2, -4});

    auto pointToVerify(search.getNearestPoint({-5, 2.5}));

    SearchForTest::Point pointToExpect{-4, 0};
    EXPECT_EQ(pointToExpect, pointToVerify);
}

}

}
