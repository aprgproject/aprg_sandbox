#include <Geometry/ThreeDimensions/EllipticHyperboloid.hpp>

#include <gtest/gtest.h>
#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

TEST(EllipticHyperboloidTest, EmptyEllipticHyperboloid)
{
    EllipticHyperboloid ellipticHyperboloid;

    EXPECT_EQ(Point(0, 0, 0), ellipticHyperboloid.getCenter());
    EXPECT_DOUBLE_EQ(0, ellipticHyperboloid.getAValue());
    EXPECT_DOUBLE_EQ(0, ellipticHyperboloid.getBValue());
    EXPECT_DOUBLE_EQ(0, ellipticHyperboloid.getCValue());
}

TEST(EllipticHyperboloidTest, EllipticHyperboloidAtOriginWithRadius)
{
    EllipticHyperboloid ellipticHyperboloid(Point(0, 0, 0), 10, 11, 12, false);

    EXPECT_EQ(Point(0, 0, 0), ellipticHyperboloid.getCenter());
    EXPECT_DOUBLE_EQ(10, ellipticHyperboloid.getAValue());
    EXPECT_DOUBLE_EQ(11, ellipticHyperboloid.getBValue());
    EXPECT_DOUBLE_EQ(12, ellipticHyperboloid.getCValue());
    EXPECT_DOUBLE_EQ(-10.097095200937051, ellipticHyperboloid.calculateXFromYAndZ(1, 2, -1));
    EXPECT_DOUBLE_EQ(-11.115504686897687, ellipticHyperboloid.calculateYFromXAndZ(3, 4, -1));
    EXPECT_DOUBLE_EQ(-8.0719901383356785, ellipticHyperboloid.calculateZFromXAndY(5, 6, -1));
}

TEST(EllipticHyperboloidTest, EllipticHyperboloidNotAtOriginWithRadius)
{
    EllipticHyperboloid ellipticHyperboloid(Point(1, 2, 3), 10, 11, 12, false);

    EXPECT_EQ(Point(1, 2, 3), ellipticHyperboloid.getCenter());
    EXPECT_DOUBLE_EQ(10, ellipticHyperboloid.getAValue());
    EXPECT_DOUBLE_EQ(11, ellipticHyperboloid.getBValue());
    EXPECT_DOUBLE_EQ(12, ellipticHyperboloid.getCValue());
    EXPECT_DOUBLE_EQ(-8.9933977286733011, ellipticHyperboloid.calculateXFromYAndZ(1, 2, -1));
    EXPECT_DOUBLE_EQ(-8.8166666666666664, ellipticHyperboloid.calculateYFromXAndZ(3, 4, -1));
    EXPECT_DOUBLE_EQ(-7.095478081099003, ellipticHyperboloid.calculateZFromXAndY(5, 6, -1));
}

TEST(EllipticHyperboloidTest, IsInsideWorks)
{
    EllipticHyperboloid ellipticHyperboloid(Point(1, 2, 3), 10, 11, 12, false);

    EXPECT_TRUE(ellipticHyperboloid.isInside(Point(0, 0, 0)));
}

}

}
