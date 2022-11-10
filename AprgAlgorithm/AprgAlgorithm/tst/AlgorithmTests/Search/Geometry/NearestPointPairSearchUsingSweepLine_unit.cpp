#include <Algorithm/Search/Geometry/NearestPointPairSearchUsingSweepLine.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using SearchForTest = NearestPointPairSearchUsingSweepLine<double>;
using PointPairForTest = SearchForTest::PointPair;
}

TEST(NearestPointPairSearchUsingSweepLineTest, GetNearestPointPairWorks)
{
    SearchForTest search;
    search.addPoint({0, 0});
    search.addPoint({3, -1});
    search.addPoint({3, -3});
    search.addPoint({-2, 0});
    search.addPoint({-2, 2});
    search.addPoint({-2, 5});
    search.addPoint({-3, -4});
    search.addPoint({-4, 0});
    search.addPoint({-1, 3});
    search.addPoint({1, -3});
    search.addPoint({2, -4});
    search.addPoint({2, 0});
    search.addPoint({2, 2});
    search.addPoint({2, 4});
    search.addPoint({6, 3});
    search.addPoint({7, 5});

    auto pointPairToVerify(search.getNearestPointPair());

    PointPairForTest pointPairToExpect{{-1, 3}, {-2, 2}};
    EXPECT_EQ(pointPairToExpect, pointPairToVerify);
}

}

}
