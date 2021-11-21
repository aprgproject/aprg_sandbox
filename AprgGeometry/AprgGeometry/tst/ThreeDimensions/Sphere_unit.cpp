#include <ThreeDimensions/Sphere.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

TEST(SphereTest, EmptySphere)
{
    Sphere circle;

    EXPECT_EQ(Point(0, 0, 0), circle.getCenter());
    EXPECT_DOUBLE_EQ(0, circle.getRadius());
}

TEST(SphereTest, SphereAtOriginWithRadius)
{
    Sphere circle(Point(0, 0, 0), 10);

    EXPECT_EQ(Point(0, 0, 0), circle.getCenter());
    EXPECT_DOUBLE_EQ(10, circle.getRadius());
    EXPECT_DOUBLE_EQ(-9.7467943448089631, circle.calculateXFromYAndZ(1, 2, -1));
    EXPECT_DOUBLE_EQ(-8.6602540378443873, circle.calculateYFromXAndZ(3, 4, -1));
    EXPECT_DOUBLE_EQ(-6.2449979983983983, circle.calculateZFromXAndY(5, 6, -1));
}

TEST(SphereTest, SphereNotAtOriginWithRadius)
{
    Sphere circle(Point(1, 2, 3), 10);

    EXPECT_EQ(Point(1, 2, 3), circle.getCenter());
    EXPECT_DOUBLE_EQ(10, circle.getRadius());
    EXPECT_DOUBLE_EQ(-8.8994949366116654, circle.calculateXFromYAndZ(1, 2, -1));
    EXPECT_DOUBLE_EQ(-7.7467943448089631, circle.calculateYFromXAndZ(3, 4, -1));
    EXPECT_DOUBLE_EQ(-5.2462112512353212, circle.calculateZFromXAndY(5, 6, -1));
}

}

}
