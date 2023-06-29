#include <Algorithm/Search/Geometry/NearestPointSearch.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SearchForTest = NearestPointSearch<double>;
using PointForTest = SearchForTest::Point;
using PointPairForTest = SearchForTest::PointPair;
}  // namespace

TEST(NearestPointSearchTest, GetNearestPointWorksWhenPointIsAtTheLeft) {
    SearchForTest search;
    search.addPoint({0, 0});
    search.addPoint({-5, 0});
    search.addPoint({5, 0});

    auto pointToVerify(search.getNearestPoint({-3, 0}));

    PointForTest pointToExpect{-5, 0};
    EXPECT_EQ(pointToExpect, pointToVerify);
}

TEST(NearestPointSearchTest, GetNearestPointWorksWhenPointIsAtTheRight) {
    SearchForTest search;
    search.addPoint({0, 0});
    search.addPoint({-5, 0});
    search.addPoint({5, 0});

    auto pointToVerify(search.getNearestPoint({3, 0}));

    PointForTest pointToExpect{5, 0};
    EXPECT_EQ(pointToExpect, pointToVerify);
}

TEST(NearestPointSearchTest, GetNearestPointWorksOnExample1) {
    SearchForTest search;
    search.addPoint({0, 0});
    search.addPoint({1, 100});
    search.addPoint({-1, -10});

    auto pointToVerify(search.getNearestPoint({1, -11}));

    PointForTest pointToExpect{-1, -10};
    EXPECT_EQ(pointToExpect, pointToVerify);
}

TEST(NearestPointSearchTest, GetNearestPointWorksOnExample2) {
    SearchForTest search;
    search.addPoint({0, 0});
    search.addPoint({3, -2});    search.addPoint({-2, 2});
    search.addPoint({-3, -4});
    search.addPoint({-4, 0});
    search.addPoint({-1, 3});    search.addPoint({1, -3});
    search.addPoint({7, 5});
    search.addPoint({6, 3});
    search.addPoint({2, -4});

    auto pointToVerify(search.getNearestPoint({-5, 2.5}));

    PointForTest pointToExpect{-4, 0};
    EXPECT_EQ(pointToExpect, pointToVerify);
}

TEST(NearestPointSearchTest, GetNearestPointPairWorksOnExample1) {
    SearchForTest search;
    search.addPoint({0, 0});
    search.addPoint({3, -1});    search.addPoint({3, -3});
    search.addPoint({-2, 0});
    search.addPoint({-2, 2});
    search.addPoint({-2, 5});    search.addPoint({-3, -4});
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

}  // namespace algorithm

}  // namespace alba
