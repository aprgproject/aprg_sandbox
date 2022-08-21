#include <Math/NumberTheory/OtherUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(OtherUtilitiesTest, IsLagrangeTheoremTrueWorks)
{
    EXPECT_FALSE(isLagrangeTheoremTrue(-13)); // Wrong input so its false, input must positive
    EXPECT_TRUE(isLagrangeTheoremTrue(13));
    EXPECT_TRUE(isLagrangeTheoremTrue(64));
    EXPECT_TRUE(isLagrangeTheoremTrue(65));
    EXPECT_TRUE(isLagrangeTheoremTrue(84));
}

TEST(OtherUtilitiesTest, IsZeckendorfTheoremTrueWorks)
{
    EXPECT_FALSE(isZeckendorfTheoremTrue(-13)); // Wrong input so its false, input must positive
    EXPECT_TRUE(isZeckendorfTheoremTrue(13));
    EXPECT_TRUE(isZeckendorfTheoremTrue(64));
    EXPECT_TRUE(isZeckendorfTheoremTrue(65));
    EXPECT_TRUE(isZeckendorfTheoremTrue(84));
}

}

}
