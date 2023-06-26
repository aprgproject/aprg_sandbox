#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Geometry/TwoDimensions/Constructs/Circle.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace TwoDimensions {

TEST(CircleTest, EmptyCircle) {
    Circle circle;

    EXPECT_EQ(Point(0, 0), circle.getCenter());
    EXPECT_DOUBLE_EQ(0, circle.getRadius());
    EXPECT_DOUBLE_EQ(0, circle.getArea());
    EXPECT_DOUBLE_EQ(0, circle.getCircumference());
    Points points(circle.getLocus(1));
    ASSERT_TRUE(points.empty());
}

TEST(CircleTest, CreateCircleFromCoefficients) {
    Circle circle(1, 6, -2, -15);

    EXPECT_EQ(Point(-3, 1), circle.getCenter());
    EXPECT_DOUBLE_EQ(5, circle.getRadius());
    EXPECT_DOUBLE_EQ(78.539816339744831, circle.getArea());
    EXPECT_DOUBLE_EQ(31.415926535897931, circle.getCircumference());
}

TEST(CircleTest, CircleAtOriginWithRadius) {
    Circle circle(Point(0, 0), 3);

    EXPECT_EQ(Point(0, 0), circle.getCenter());
    EXPECT_DOUBLE_EQ(3, circle.getRadius());
    EXPECT_DOUBLE_EQ(28.274333882308138044, circle.getArea());
    EXPECT_DOUBLE_EQ(18.849555921538758696, circle.getCircumference());
    Points points(circle.getLocus(1));
    ASSERT_EQ(20U, points.size());
    EXPECT_EQ(Point(3, 0), points[0]);
    EXPECT_EQ(Point(2.8284271247461902909, 1), points[1]);
    EXPECT_EQ(Point(2.2360679774997898051, 2), points[2]);
    EXPECT_EQ(Point(2, 2.2360679774997898051), points[3]);
    EXPECT_EQ(Point(1, 2.8284271247461902909), points[4]);
    EXPECT_EQ(Point(0, 3), points[5]);
    EXPECT_EQ(Point(-1, 2.8284271247461902909), points[6]);
    EXPECT_EQ(Point(-2, 2.2360679774997898051), points[7]);
    EXPECT_EQ(Point(-2.2360679774997898051, 2), points[8]);
    EXPECT_EQ(Point(-2.8284271247461902909, 1), points[9]);
    EXPECT_EQ(Point(-3, 0), points[10]);
    EXPECT_EQ(Point(-2.8284271247461902909, -1), points[11]);
    EXPECT_EQ(Point(-2.2360679774997898051, -2), points[12]);
    EXPECT_EQ(Point(-2, -2.2360679774997898051), points[13]);
    EXPECT_EQ(Point(-1, -2.8284271247461902909), points[14]);
    EXPECT_EQ(Point(0, -3), points[15]);
    EXPECT_EQ(Point(1, -2.8284271247461902909), points[16]);
    EXPECT_EQ(Point(2, -2.2360679774997898051), points[17]);
    EXPECT_EQ(Point(2.2360679774997898051, -2), points[18]);
    EXPECT_EQ(Point(2.8284271247461902909, -1), points[19]);
}

TEST(CircleTest, IsInsideWorks) {    Circle circle(Point(0, 0), 3);

    EXPECT_TRUE(circle.isInside(Point(1, 1)));
    EXPECT_FALSE(circle.isInside(Point(100, 100)));}

TEST(CircleTest, GetEccentricityWorks) {
    Circle circle(1, 6, -2, -15);

    EXPECT_DOUBLE_EQ(0, circle.getEccentricity());
}

TEST(CircleTest, GetPointAtAngleWorks) {
    Circle circle(Point(1, 2), 3);
    EXPECT_EQ(Point(4, 2), circle.getPointAtAngle(0));
    EXPECT_EQ(Point(1, 5), circle.getPointAtAngle(getPi() / 2));
    EXPECT_EQ(Point(-2, 2), circle.getPointAtAngle(getPi()));
    EXPECT_EQ(Point(1, -1), circle.getPointAtAngle(getPi() * 3 / 2));
    EXPECT_EQ(Point(4, 2), circle.getPointAtAngle(getPi() * 2));
}

TEST(CircleTest, GetNearestPointAtCircumferenceWorks) {
    Circle circle(Point(1, 2), 3);
    EXPECT_EQ(Point(3.4, 3.8), circle.getNearestPointInCircumference(Point(5, 5)));
}

TEST(CircleTest, PointsInAreaTraversalIsCorrect) {
    Circle circle(Point(3, 3), 2);
    Points pointsInAreaTraversal;

    circle.traverseArea(1, [&](Point const& pointInArea) { pointsInAreaTraversal.emplace_back(pointInArea); });

    ASSERT_EQ(13U, pointsInAreaTraversal.size());
    EXPECT_EQ(Point(3, 3), pointsInAreaTraversal[0]);
    EXPECT_EQ(Point(4, 3), pointsInAreaTraversal[1]);
    EXPECT_EQ(Point(2, 3), pointsInAreaTraversal[2]);
    EXPECT_EQ(Point(5, 3), pointsInAreaTraversal[3]);
    EXPECT_EQ(Point(1, 3), pointsInAreaTraversal[4]);
    EXPECT_EQ(Point(3, 4), pointsInAreaTraversal[5]);
    EXPECT_EQ(Point(3, 2), pointsInAreaTraversal[6]);
    EXPECT_EQ(Point(4, 4), pointsInAreaTraversal[7]);
    EXPECT_EQ(Point(2, 4), pointsInAreaTraversal[8]);
    EXPECT_EQ(Point(4, 2), pointsInAreaTraversal[9]);
    EXPECT_EQ(Point(2, 2), pointsInAreaTraversal[10]);
    EXPECT_EQ(Point(3, 5), pointsInAreaTraversal[11]);
    EXPECT_EQ(Point(3, 1), pointsInAreaTraversal[12]);
}

}  // namespace TwoDimensions
}  // namespace alba