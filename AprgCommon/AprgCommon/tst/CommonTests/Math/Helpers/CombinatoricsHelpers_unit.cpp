#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::mathHelper {

TEST(CombinatoricsHelpersTest, GetNumberOfPossibilitiesWorks) {
    EXPECT_EQ(1U, getNumberOfPossibilities(0U, 0U));
    EXPECT_EQ(1U, getNumberOfPossibilities(1U, 1U));
    EXPECT_EQ(1U, getNumberOfPossibilities(0U, 0U));
    EXPECT_EQ(8U, getNumberOfPossibilities(2U, 3U));
    EXPECT_EQ(3125U, getNumberOfPossibilities(5U, 5U));
}

TEST(CombinatoricsHelpersTest, GetFactorialWorks) {
    EXPECT_EQ(1U, getFactorial(0U));
    EXPECT_EQ(1U, getFactorial(1U));
    EXPECT_EQ(120U, getFactorial(5U));
    EXPECT_EQ(3628800U, getFactorial(10U));
}

TEST(CombinatoricsHelpersTest, GetNumberOfPermutationsWorks) {
    EXPECT_EQ(24U, getNumberOfPermutations(4U, 4U));
    EXPECT_EQ(1U, getNumberOfPermutations(4U, 0U));
    EXPECT_EQ(4U, getNumberOfPermutations(4U, 1U));
    EXPECT_EQ(0U, getNumberOfPermutations(4U, 5U));
}

TEST(CombinatoricsHelpersTest, GetNumberOfCombinationsWorks) {
    EXPECT_EQ(10U, getNumberOfCombinations(5U, 2U));
    EXPECT_EQ(1U, getNumberOfCombinations(4U, 4U));
    EXPECT_EQ(1U, getNumberOfCombinations(4U, 0U));
    EXPECT_EQ(4U, getNumberOfCombinations(4U, 1U));
    EXPECT_EQ(0U, getNumberOfCombinations(4U, 5U));
    EXPECT_EQ(2333606220U, getNumberOfCombinations(34U, 17U));
}

TEST(CombinatoricsHelpersTest, GetValueAtPascalTriangleWorks) {
    EXPECT_EQ(1U, getValueAtPascalTriangle(0U, 0U));
    EXPECT_EQ(1U, getValueAtPascalTriangle(4U, 4U));
    EXPECT_EQ(1U, getValueAtPascalTriangle(4U, 0U));
    EXPECT_EQ(4U, getValueAtPascalTriangle(4U, 1U));
    EXPECT_EQ(6U, getValueAtPascalTriangle(4U, 2U));
    EXPECT_EQ(0U, getValueAtPascalTriangle(4U, 5U));
}

TEST(CombinatoricsHelpersTest, GetStirlingNumberOfTheSecondKindWorks) {
    EXPECT_EQ(1, getStirlingNumberOfTheSecondKind(0U, 0U));
    EXPECT_EQ(0, getStirlingNumberOfTheSecondKind(3U, 0U));
    EXPECT_EQ(1, getStirlingNumberOfTheSecondKind(3U, 1U));
    EXPECT_EQ(3, getStirlingNumberOfTheSecondKind(3U, 2U));
    EXPECT_EQ(1, getStirlingNumberOfTheSecondKind(3U, 3U));
    EXPECT_EQ(0, getStirlingNumberOfTheSecondKind(10U, 0U));
    EXPECT_EQ(1, getStirlingNumberOfTheSecondKind(10U, 1U));
    EXPECT_EQ(511, getStirlingNumberOfTheSecondKind(10U, 2U));
    EXPECT_EQ(42525, getStirlingNumberOfTheSecondKind(10U, 5U));
    EXPECT_EQ(344, getStirlingNumberOfTheSecondKind(10U, 10U));
}

}  // namespace alba::mathHelper
