#include <Geometry/TwoDimensions/Constructs/Quadrilateral.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace TwoDimensions {

TEST(QuadrilateralTest, QuadilateralCanBeCreated) {
    Quadrilateral quadrilateral(Point(1, 1), Point(2, 3), Point(0, 17), Point(-100, 4));
}

TEST(QuadrilateralTest, GetPointsWorks) {
    Quadrilateral quadrilateral(Point(-2, 0), Point(0, -2), Point(2, 0), Point(0, 2));
    Points points(quadrilateral.getPoints(1));

    ASSERT_EQ(8U, points.size());
    EXPECT_EQ(Point(-2, 0), points.at(0));
    EXPECT_EQ(Point(-1, -1), points.at(1));
    EXPECT_EQ(Point(0, -2), points.at(2));
    EXPECT_EQ(Point(1, -1), points.at(3));
    EXPECT_EQ(Point(2, 0), points.at(4));
    EXPECT_EQ(Point(1, 1), points.at(5));
    EXPECT_EQ(Point(0, 2), points.at(6));
    EXPECT_EQ(Point(-1, 1), points.at(7));
}

TEST(QuadrilateralTest, DISABLED_PointsInQuadilateralAreCorrectWhenOutOfOrderVerticesAreUsed) {
    // how can this be done?
    Quadrilateral quadrilateral(Point(-2, 0), Point(2, 0), Point(0, 2), Point(0, -2));
    Points points(quadrilateral.getPoints(1));

    ASSERT_EQ(8U, points.size());
    EXPECT_EQ(Point(-2, 0), points.at(0));
    EXPECT_EQ(Point(-1, -1), points.at(1));
    EXPECT_EQ(Point(0, -2), points.at(2));
    EXPECT_EQ(Point(1, -1), points.at(3));
    EXPECT_EQ(Point(2, 0), points.at(4));
    EXPECT_EQ(Point(1, 1), points.at(5));
    EXPECT_EQ(Point(0, 2), points.at(6));
    EXPECT_EQ(Point(-1, 1), points.at(7));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor1YGroup) {
    Quadrilateral quadrilateral(Point(1, 1), Point(2, 1), Point(4, 1), Point(5, 1));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(5U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(1, 1), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(2, 1), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(4, 1), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(5, 1), pointsInAreaTraversal.at(4));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor2YGroupsInFirstPattern) {
    Quadrilateral quadrilateral(Point(3, 1), Point(1, 3), Point(3, 3), Point(5, 3));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(1, 3), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal.at(7));
    EXPECT_EQ(Point(5, 3), pointsInAreaTraversal.at(8));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor2YGroupsInSecondPattern) {
    Quadrilateral quadrilateral(Point(2, 2), Point(2, 4), Point(4, 2), Point(4, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal.at(7));
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal.at(8));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor2YGroupsInThirdPattern) {
    Quadrilateral quadrilateral(Point(3, 5), Point(1, 3), Point(3, 3), Point(5, 3));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(1, 3), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(5, 3), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal.at(7));
    EXPECT_EQ(Point(3, 5), pointsInAreaTraversal.at(8));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInFirstPattern) {
    Quadrilateral quadrilateral(Point(2, 1), Point(4, 3), Point(2, 4), Point(4, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2, 1), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal.at(7));
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal.at(8));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInSecondPattern) {
    Quadrilateral quadrilateral(Point(4, 1), Point(2, 3), Point(2, 4), Point(4, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(4, 1), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal.at(7));
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal.at(8));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInThirdPattern) {
    Quadrilateral quadrilateral(Point(3, 1), Point(1, 2), Point(5, 2), Point(3, 3));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(7U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(1, 2), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(5, 2), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal.at(6));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInFourthPattern) {
    Quadrilateral quadrilateral(Point(2, 3), Point(4, 5), Point(2, 2), Point(4, 2));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal.at(7));
    EXPECT_EQ(Point(4, 5), pointsInAreaTraversal.at(8));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor3YGroupsInFifthPattern) {
    Quadrilateral quadrilateral(Point(2, 5), Point(4, 3), Point(2, 2), Point(4, 2));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(9U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal.at(7));
    EXPECT_EQ(Point(2, 5), pointsInAreaTraversal.at(8));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor4YGroupsFirstPattern) {
    Quadrilateral quadrilateral(Point(3, 1), Point(2, 2), Point(4, 3), Point(3, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(8U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(3.5, 2), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(2.5, 3), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(3.5, 3), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal.at(7));
}

TEST(QuadrilateralTest, PointsInAreaTraversalIsCorrectFor4YGroupsSecondPattern) {
    Quadrilateral quadrilateral(Point(3, 1), Point(2, 3), Point(4, 2), Point(3, 4));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(8U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal.at(0));
    EXPECT_EQ(Point(2.5, 2), pointsInAreaTraversal.at(1));
    EXPECT_EQ(Point(3.5, 2), pointsInAreaTraversal.at(2));
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal.at(3));
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal.at(4));
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal.at(5));
    EXPECT_EQ(Point(3.5, 3), pointsInAreaTraversal.at(6));
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal.at(7));
}

TEST(QuadrilateralTest, DoesNotCrashExampleDueToNearValues) {
    Quadrilateral quadrilateral(
        Point(3.57038804403507858964417209791, 37.7082039324993658624407544266),
        Point(-3.57038804403508036600101149816, 37.7082039324993729678681120276),
        Point(2.66121012417164948260506207589, 36.2917960675006270321318879724),
        Point(-2.66121012417165125896190147614, 36.2917960675006341375592455734));
    Points pointsInAreaTraversal;

    quadrilateral.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    EXPECT_EQ(24U, pointsInAreaTraversal.size());
}

}  // namespace TwoDimensions

}  // namespace alba
