#include <Math/Combinatorics/OtherUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(OtherUtilitiesTest, IsBinomialCoefficientEqualToItsCounterpartWorks)
{
    EXPECT_FALSE(isBinomialCoefficientEqualToItsCounterpart(2U, 4U)); // Wrong input so its false, it should ben>k
    EXPECT_TRUE(isBinomialCoefficientEqualToItsCounterpart(4U, 2U));
    EXPECT_TRUE(isBinomialCoefficientEqualToItsCounterpart(10U, 5U));
}

TEST(OtherUtilitiesTest, IsTheSumOfBinomialCoefficientsEqualTo2ToTheNWorks)
{
    EXPECT_TRUE(isTheSumOfBinomialCoefficientsEqualTo2ToTheN(4U));
    EXPECT_TRUE(isTheSumOfBinomialCoefficientsEqualTo2ToTheN(10U));}

}
}
