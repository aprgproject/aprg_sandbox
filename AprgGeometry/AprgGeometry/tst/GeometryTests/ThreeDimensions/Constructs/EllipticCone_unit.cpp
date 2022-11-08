#include <Geometry/ThreeDimensions/Constructs/EllipticCone.hpp>

#include <gtest/gtest.h>
#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

TEST(EllipticConeTest, EmptyEllipticCone)
{
    EllipticCone ellipticCone;

    EXPECT_EQ(Point(0, 0, 0), ellipticCone.getCenter());
    EXPECT_DOUBLE_EQ(0, ellipticCone.getAValue());
    EXPECT_DOUBLE_EQ(0, ellipticCone.getBValue());
    EXPECT_DOUBLE_EQ(0, ellipticCone.getCValue());
}

TEST(EllipticConeTest, EllipticConeAtOriginWithRadius)
{
    EllipticCone ellipticCone(Point(0, 0, 0), 4, 5, 12);

    EXPECT_EQ(Point(0, 0, 0), ellipticCone.getCenter());
    EXPECT_DOUBLE_EQ(4, ellipticCone.getAValue());
    EXPECT_DOUBLE_EQ(5, ellipticCone.getBValue());
    EXPECT_DOUBLE_EQ(12, ellipticCone.getCValue());
    EXPECT_DOUBLE_EQ(0, ellipticCone.calculateXFromYAndZ(0, 0, 1));
    EXPECT_DOUBLE_EQ(0, ellipticCone.calculateYFromXAndZ(0, 0, 1));
    EXPECT_DOUBLE_EQ(0, ellipticCone.calculateZFromXAndY(0, 0, 1));
}

TEST(EllipticConeTest, EllipticConeNotAtOriginWithRadius)
{
    EllipticCone ellipticCone(Point(1, 2, 3), 4, 5, 12);

    EXPECT_EQ(Point(1, 2, 3), ellipticCone.getCenter());
    EXPECT_DOUBLE_EQ(4, ellipticCone.getAValue());
    EXPECT_DOUBLE_EQ(5, ellipticCone.getBValue());
    EXPECT_DOUBLE_EQ(12, ellipticCone.getCValue());
    EXPECT_DOUBLE_EQ(1, ellipticCone.calculateXFromYAndZ(2, 3, 1));
    EXPECT_DOUBLE_EQ(2, ellipticCone.calculateYFromXAndZ(1, 3, 1));
    EXPECT_DOUBLE_EQ(3, ellipticCone.calculateZFromXAndY(1, 2, 1));
}

}

}
