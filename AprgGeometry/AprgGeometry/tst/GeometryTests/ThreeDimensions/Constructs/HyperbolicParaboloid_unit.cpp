#include <Geometry/ThreeDimensions/Constructs/HyperbolicParaboloid.hpp>

#include <gtest/gtest.h>
#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

TEST(HyperbolicParaboloidTest, EmptyHyperbolicParaboloid)
{
    HyperbolicParaboloid hyperbolicParaboloid;

    EXPECT_EQ(Point(0, 0, 0), hyperbolicParaboloid.getCenter());
    EXPECT_DOUBLE_EQ(0, hyperbolicParaboloid.getAValue());
    EXPECT_DOUBLE_EQ(0, hyperbolicParaboloid.getBValue());
    EXPECT_DOUBLE_EQ(0, hyperbolicParaboloid.getCValue());
}

TEST(HyperbolicParaboloidTest, HyperbolicParaboloidAtOriginWithRadius)
{
    HyperbolicParaboloid hyperbolicParaboloid(Point(0, 0, 0), 10, 5, 10);

    EXPECT_EQ(Point(0, 0, 0), hyperbolicParaboloid.getCenter());
    EXPECT_DOUBLE_EQ(10, hyperbolicParaboloid.getAValue());
    EXPECT_DOUBLE_EQ(5, hyperbolicParaboloid.getBValue());
    EXPECT_DOUBLE_EQ(10, hyperbolicParaboloid.getCValue());
    EXPECT_DOUBLE_EQ(2, hyperbolicParaboloid.calculateXFromYAndZ(1, 0, 1));
    EXPECT_DOUBLE_EQ(3.5, hyperbolicParaboloid.calculateYFromXAndZ(3, 4, 1));
    EXPECT_DOUBLE_EQ(11.899999999999999, hyperbolicParaboloid.calculateZFromXAndY(5, 6));
}

TEST(HyperbolicParaboloidTest, HyperbolicParaboloidNotAtOriginWithRadius)
{
    HyperbolicParaboloid hyperbolicParaboloid(Point(1, 2, 3), 10, 5, 10);

    EXPECT_EQ(Point(1, 2, 3), hyperbolicParaboloid.getCenter());
    EXPECT_DOUBLE_EQ(10, hyperbolicParaboloid.getAValue());
    EXPECT_DOUBLE_EQ(5, hyperbolicParaboloid.getBValue());
    EXPECT_DOUBLE_EQ(10, hyperbolicParaboloid.getCValue());
    EXPECT_DOUBLE_EQ(6.8309518948453007, hyperbolicParaboloid.calculateXFromYAndZ(1, 0, 1));
    EXPECT_DOUBLE_EQ(3.8708286933869709, hyperbolicParaboloid.calculateYFromXAndZ(3, 4, 1));
    EXPECT_DOUBLE_EQ(7.8000000000000007, hyperbolicParaboloid.calculateZFromXAndY(5, 6));
}

}

}
