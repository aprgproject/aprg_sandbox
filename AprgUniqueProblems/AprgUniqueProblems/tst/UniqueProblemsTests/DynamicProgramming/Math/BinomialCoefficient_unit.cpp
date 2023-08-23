#include <UniqueProblems/DynamicProgramming/Math/BinomialCoefficient.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(BinomialCoefficientTest, GetMinimumNumberOfOperationsWorksOnExample1) {
    BinomialCoefficient queryForTest(0, 0);

    EXPECT_EQ(1, queryForTest.getBinomialCoefficientUsingNaiveRecursion());
    EXPECT_EQ(1, queryForTest.getBinomialCoefficientUsingMemoizationDP());
    EXPECT_EQ(1, queryForTest.getBinomialCoefficientUsingIterativeDP());
    EXPECT_EQ(1, queryForTest.getBinomialCoefficientUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(1, queryForTest.getBinomialCoefficientUsingGcf());
}

TEST(BinomialCoefficientTest, GetMinimumNumberOfOperationsWorksOnExample2) {
    BinomialCoefficient queryForTest(5, 2);

    EXPECT_EQ(10, queryForTest.getBinomialCoefficientUsingNaiveRecursion());
    EXPECT_EQ(10, queryForTest.getBinomialCoefficientUsingMemoizationDP());
    EXPECT_EQ(10, queryForTest.getBinomialCoefficientUsingIterativeDP());
    EXPECT_EQ(10, queryForTest.getBinomialCoefficientUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(10, queryForTest.getBinomialCoefficientUsingGcf());
}

TEST(BinomialCoefficientTest, GetMinimumNumberOfOperationsWorksOnExample3) {
    BinomialCoefficient queryForTest(34, 17);

    // EXPECT_EQ(2333606220, queryForTest.getBinomialCoefficientUsingNaiveRecursion()); // Too long
    EXPECT_EQ(2333606220, queryForTest.getBinomialCoefficientUsingMemoizationDP());
    EXPECT_EQ(2333606220, queryForTest.getBinomialCoefficientUsingIterativeDP());
    EXPECT_EQ(2333606220, queryForTest.getBinomialCoefficientUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(2333606220, queryForTest.getBinomialCoefficientUsingGcf());
}

}  // namespace alba
