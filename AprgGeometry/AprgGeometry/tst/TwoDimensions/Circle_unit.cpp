#include <TwoDimensions/Circle.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::TwoDimensions;
using namespace std;


TEST(CircleTest, EmptyCircle)
{
    Circle circle;

    EXPECT_EQ(Point(0,0), circle.getCenter());
    EXPECT_EQ(0, circle.getRadius());
    EXPECT_EQ(0, circle.getArea());
    EXPECT_EQ(0, circle.getCircumference());

    Points points(circle.getPointsForCircumference(1));
    ASSERT_TRUE(points.empty());
}

TEST(CircleTest, CircleAtOriginWithRadius)
{
    Circle circle(Point(0,0), 3);

    EXPECT_EQ(Point(0,0), circle.getCenter());
    EXPECT_EQ(3, circle.getRadius());
    EXPECT_EQ(28.274333882308138044, circle.getArea());
    EXPECT_EQ(18.849555921538758696, circle.getCircumference());

    Points points(circle.getPointsForCircumference(1));
    ASSERT_EQ(20u, points.size());
    EXPECT_EQ(Point(3,0), points[0]);
    EXPECT_EQ(Point(2.8284271247461902909,1), points[1]);
    EXPECT_EQ(Point(2.2360679774997898051,2), points[2]);
    EXPECT_EQ(Point(2,2.2360679774997898051), points[3]);
    EXPECT_EQ(Point(1,2.8284271247461902909), points[4]);
    EXPECT_EQ(Point(0,3), points[5]);
    EXPECT_EQ(Point(-1,2.8284271247461902909), points[6]);
    EXPECT_EQ(Point(-2,2.2360679774997898051), points[7]);
    EXPECT_EQ(Point(-2.2360679774997898051,2), points[8]);
    EXPECT_EQ(Point(-2.8284271247461902909,1), points[9]);
    EXPECT_EQ(Point(-3,0), points[10]);
    EXPECT_EQ(Point(-2.8284271247461902909,-1), points[11]);
    EXPECT_EQ(Point(-2.2360679774997898051,-2), points[12]);
    EXPECT_EQ(Point(-2,-2.2360679774997898051), points[13]);
    EXPECT_EQ(Point(-1,-2.8284271247461902909), points[14]);
    EXPECT_EQ(Point(0,-3), points[15]);
    EXPECT_EQ(Point(1,-2.8284271247461902909), points[16]);
    EXPECT_EQ(Point(2,-2.2360679774997898051), points[17]);
    EXPECT_EQ(Point(2.2360679774997898051,-2), points[18]);
    EXPECT_EQ(Point(2.8284271247461902909,-1), points[19]);
}

TEST(CircleTest, GetNearestPointAtCircumference)
{
    Circle circle(Point(1,2), 3);
    EXPECT_EQ(Point(3.4,3.8), circle.getNearestPointInCircumference(Point(5,5)));
}

TEST(CircleTest, AreaTraversalIsCorrect)
{
    //traversal
}


