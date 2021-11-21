#include <ThreeDimensions/EllipticParaboloid.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

TEST(EllipticParaboloidTest, EmptyEllipticParaboloid)
{
    EllipticParaboloid ellipticParaboloid;

    EXPECT_EQ(Point(0, 0, 0), ellipticParaboloid.getCenter());
    EXPECT_DOUBLE_EQ(0, ellipticParaboloid.getAValue());
    EXPECT_DOUBLE_EQ(0, ellipticParaboloid.getBValue());
    EXPECT_DOUBLE_EQ(0, ellipticParaboloid.getCValue());
}

TEST(EllipticParaboloidTest, EllipticParaboloidAtOriginWithRadius)
{
    EllipticParaboloid ellipticParaboloid(Point(0, 0, 0), 10, 11, 12);

    EXPECT_EQ(Point(0, 0, 0), ellipticParaboloid.getCenter());
    EXPECT_DOUBLE_EQ(10, ellipticParaboloid.getAValue());
    EXPECT_DOUBLE_EQ(11, ellipticParaboloid.getBValue());
    EXPECT_DOUBLE_EQ(12, ellipticParaboloid.getCValue());
    EXPECT_DOUBLE_EQ(-3.9799774353223323, ellipticParaboloid.calculateXFromYAndZ(1, 2, -1));
    EXPECT_DOUBLE_EQ(-5.4261711485478719, ellipticParaboloid.calculateYFromXAndZ(3, 4, -1));
    EXPECT_DOUBLE_EQ(6.5702479338842972, ellipticParaboloid.calculateZFromXAndY(5, 6));
}

TEST(EllipticParaboloidTest, EllipticParaboloidNotAtOriginWithRadius)
{
    EllipticParaboloid ellipticParaboloid(Point(1, 2, 3), 10, 11, 12);

    EXPECT_EQ(Point(1, 2, 3), ellipticParaboloid.getCenter());
    EXPECT_DOUBLE_EQ(10, ellipticParaboloid.getAValue());
    EXPECT_DOUBLE_EQ(11, ellipticParaboloid.getBValue());
    EXPECT_DOUBLE_EQ(12, ellipticParaboloid.getCValue());
    EXPECT_DOUBLE_EQ(-2.9799774353223323, ellipticParaboloid.calculateXFromYAndZ(1, 2, -1));
    EXPECT_DOUBLE_EQ(-3.9576281633997041, ellipticParaboloid.calculateYFromXAndZ(3, 4, -1));
    EXPECT_DOUBLE_EQ(3.5067768595041326, ellipticParaboloid.calculateZFromXAndY(5, 6));
}

}

}
