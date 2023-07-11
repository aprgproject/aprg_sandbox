#include <AprgUniqueProblems/BitManipulation/UniqueElement.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(UniqueElementTest, GetAUniqueElementOnTwoDuplicatedValuesWorksOnExample1) {
    UniqueElement::Values values{2, 3, 7, 11, 2, 3, 11};
    UniqueElement solution;

    EXPECT_EQ(7U, solution.getAUniqueElementOnTwoDuplicatedValues(values));
}

TEST(UniqueElementTest, GetTwoUniqueElementsOnTwoDuplicatedValuesOnExample1) {
    UniqueElement::Values values{2, 3, 7, 9, 11, 2, 3, 11};
    UniqueElement solution;

    UniqueElement::ValuePairs expectedPair{7U, 9U};
    EXPECT_EQ(expectedPair, solution.getTwoUniqueElementsOnTwoDuplicatedValues(values));
}

TEST(UniqueElementTest, GetAUniqueElementOnThreeDuplicatedValuesWorksOnExample1) {
    UniqueElement::Values values{12, 1, 12, 3, 12, 1, 1, 2, 3, 3};
    UniqueElement solution;

    EXPECT_EQ(2U, solution.getAUniqueElementOnThreeDuplicatedValues(values));
}

TEST(UniqueElementTest, GetAnElementOccuringOddNumberOfTimesWorksOnExample1) {
    UniqueElement::Values values{5, 7, 2, 7, 5, 2, 5};
    UniqueElement solution;

    EXPECT_EQ(5U, solution.getAnElementOccuringOddNumberOfTimes(values));
}

}  // namespace alba
