#include <Algebra/Solution/SolutionUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

TEST(SolutionUtilitiesTest, GetPositiveLogarithmOfLargestNumberWorks) {
    EXPECT_EQ(AlbaNumber(6.90775527898214), getPositiveLogarithmOfLargestNumber(1000));
    EXPECT_EQ(AlbaNumber(0), getPositiveLogarithmOfLargestNumber("x"));
}

TEST(SolutionUtilitiesTest, GetInitialValuesForIteratingMethodsWorksForTerm) {
    AlbaNumbers actualValues(getInitialValuesForIteratingMethods(Monomial(123, {{"x", 456}})));

    ASSERT_EQ(8U, actualValues.size());
    EXPECT_DOUBLE_EQ(-456, actualValues[0].getDouble());
    EXPECT_DOUBLE_EQ(-123, actualValues[1].getDouble());
    EXPECT_DOUBLE_EQ(-6.1224928095143865, actualValues[2].getDouble());
    EXPECT_DOUBLE_EQ(-4.8121843553724171, actualValues[3].getDouble());
    EXPECT_DOUBLE_EQ(4.8121843553724171, actualValues[4].getDouble());
    EXPECT_DOUBLE_EQ(6.1224928095143865, actualValues[5].getDouble());
    EXPECT_DOUBLE_EQ(123, actualValues[6].getDouble());
    EXPECT_DOUBLE_EQ(456, actualValues[7].getDouble());
}

TEST(SolutionUtilitiesTest, GetInitialValuesForIteratingMethodsWorksForEquation) {
    AlbaNumbers actualValues(
        getInitialValuesForIteratingMethods(Equation(Monomial(1, {{"x", 123}}), "=", Monomial(1, {{"x", 456}}))));

    ASSERT_EQ(11U, actualValues.size());
    EXPECT_DOUBLE_EQ(-456, actualValues[0].getDouble());
    EXPECT_DOUBLE_EQ(-123, actualValues[1].getDouble());
    EXPECT_DOUBLE_EQ(-6.1224928095143865, actualValues[2].getDouble());
    EXPECT_DOUBLE_EQ(-4.8121843553724171, actualValues[3].getDouble());
    EXPECT_DOUBLE_EQ(-1, actualValues[4].getDouble());
    EXPECT_DOUBLE_EQ(0, actualValues[5].getDouble());
    EXPECT_DOUBLE_EQ(1, actualValues[6].getDouble());
    EXPECT_DOUBLE_EQ(4.8121843553724171, actualValues[7].getDouble());
    EXPECT_DOUBLE_EQ(6.1224928095143865, actualValues[8].getDouble());
    EXPECT_DOUBLE_EQ(123, actualValues[9].getDouble());
    EXPECT_DOUBLE_EQ(456, actualValues[10].getDouble());
}

}  // namespace algebra

}  // namespace alba
