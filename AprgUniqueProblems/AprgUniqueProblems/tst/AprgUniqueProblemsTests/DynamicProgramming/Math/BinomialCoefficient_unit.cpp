#include <AprgUniqueProblems/DynamicProgramming/Math/BinomialCoefficient.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BinomialCoefficientTest, GetMinimumNumberOfOperationsWorksOnExample1)
{
    BinomialCoefficient queryForTest(0U, 0U);

    EXPECT_EQ(1U, queryForTest.getBinomialCoefficientUsingNaiveRecursion());
    EXPECT_EQ(1U, queryForTest.getBinomialCoefficientUsingMemoizationDP());
    EXPECT_EQ(1U, queryForTest.getBinomialCoefficientUsingIterativeDP());
    EXPECT_EQ(1U, queryForTest.getBinomialCoefficientUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(1U, queryForTest.getBinomialCoefficientUsingGcf());
}

TEST(BinomialCoefficientTest, GetMinimumNumberOfOperationsWorksOnExample2)
{
    BinomialCoefficient queryForTest(5U, 2U);
    EXPECT_EQ(10U, queryForTest.getBinomialCoefficientUsingNaiveRecursion());
    EXPECT_EQ(10U, queryForTest.getBinomialCoefficientUsingMemoizationDP());
    EXPECT_EQ(10U, queryForTest.getBinomialCoefficientUsingIterativeDP());
    EXPECT_EQ(10U, queryForTest.getBinomialCoefficientUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(10U, queryForTest.getBinomialCoefficientUsingGcf());
}

TEST(BinomialCoefficientTest, GetMinimumNumberOfOperationsWorksOnExample3)
{
    BinomialCoefficient queryForTest(34U, 17U);
    // EXPECT_EQ(2333606220U, queryForTest.getBinomialCoefficientUsingNaiveRecursion()); // Too long
    EXPECT_EQ(2333606220U, queryForTest.getBinomialCoefficientUsingMemoizationDP());
    EXPECT_EQ(2333606220U, queryForTest.getBinomialCoefficientUsingIterativeDP());
    EXPECT_EQ(2333606220U, queryForTest.getBinomialCoefficientUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(2333606220U, queryForTest.getBinomialCoefficientUsingGcf());
}

}