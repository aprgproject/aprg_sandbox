#include <Math/NumberTheory/PrimeAndFactorUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(PrimeAndFactorUtilitiesTest, IsNumberOfPrimesInfiniteWorks)
{
    // The factors are 1, 2, 3, 4, 6, 7, 12, 14, 21, 28, 42 and 84.

    EXPECT_TRUE(isNumberOfPrimesInfinite());
}

TEST(PrimeAndFactorUtilitiesTest, IsGoldbachConjectureTrueWorks)
{
    EXPECT_FALSE(isGoldbachConjectureTrue(83)); // Wrong input so its false, input must be even!
    EXPECT_TRUE(isGoldbachConjectureTrue(12));
    EXPECT_TRUE(isGoldbachConjectureTrue(64));
    EXPECT_TRUE(isGoldbachConjectureTrue(84));
}

TEST(PrimeAndFactorUtilitiesTest, IsTwinPrimeConjectureTrueWorks)
{
    EXPECT_TRUE(isTwinPrimeConjectureTrue(13));
    EXPECT_TRUE(isTwinPrimeConjectureTrue(64));
    EXPECT_TRUE(isTwinPrimeConjectureTrue(65));
    EXPECT_TRUE(isTwinPrimeConjectureTrue(84));
}

TEST(PrimeAndFactorUtilitiesTest, IsLegendreConjectureTrueWorks)
{
    EXPECT_TRUE(isLegendreConjectureTrue(13));
    EXPECT_TRUE(isLegendreConjectureTrue(64));
    EXPECT_TRUE(isLegendreConjectureTrue(65));
    EXPECT_TRUE(isLegendreConjectureTrue(84));
}

TEST(PrimeAndFactorUtilitiesTest, GetNumberOfFactorsWorks)
{
    // The factors are 1, 2, 3, 4, 6, 7, 12, 14, 21, 28, 42 and 84.

    EXPECT_EQ(12U, getNumberOfFactors(84U));
}

TEST(PrimeAndFactorUtilitiesTest, GetSumOfFactorsWorks)
{
    // 1 + 2 + 3 + 4 + 6 + 7 + 12 + 14 + 21 + 28 + 42 + 84 = 224

    EXPECT_EQ(224U, getSumOfFactors(84U));
}

TEST(PrimeAndFactorUtilitiesTest, GetProductOfFactorsWorks)
{
    // 1 * 2 * 3 * 4 * 6 * 7 * 12 * 14 * 21 * 28 * 42 * 84 = 224

    EXPECT_EQ(351298031616U, getProductOfFactors(84U));
}

TEST(PrimeAndFactorUtilitiesTest, GetApproximateDensityOfPrimesWorks)
{
    // The number of primes between 1 to 10^6 is 78498 and 72382 is a good approximation.

    EXPECT_EQ(72382U, getApproximateDensityOfPrimes(1000000U));
}

TEST(PrimeAndFactorUtilitiesTest, GetPrimesBeforeThisNumberWorks)
{
    Numbers expectedNumbers{2U, 3U, 5U, 7U, 11U, 13U, 17U, 19U, 23U, 29U};

    EXPECT_EQ(expectedNumbers, getPrimesBeforeThisNumber(30U));
}

TEST(PrimeAndFactorUtilitiesTest, GetPrimeFactorsOfNumberWorks)
{
    Numbers expectedNumbers{2U, 2U, 3U, 7U};

    EXPECT_EQ(expectedNumbers, getPrimeFactorsOfNumber(84U));
}

TEST(PrimeAndFactorUtilitiesTest, GetPrimeFactorsToCountMapWorks)
{
    FactorsToCountMap expectedMap{{2U, 2U}, {3U, 1U}, {7U, 1U}};

    EXPECT_EQ(expectedMap, getPrimeFactorsToCountMap(84U));
}

}

}
