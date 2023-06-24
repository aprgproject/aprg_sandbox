#include <Algorithm/Sort/QuickSorter/QuickSelector.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSelector.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSelector;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Characters = vector<char>;
using Integers = vector<int>;
using CharacterSelector = QuickSelector<Characters>;
using IntegerSelector = QuickSelector<Integers>;
}  // namespace

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1) {
    CharacterSelector selector(PivotType::LowestIndex);
    testDoNthElementUsingExample1WithCharacters<CharacterSelector, Characters>(selector);
}

TEST(QuickSelectorTest, DoNthSelectWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegerSelector selector(PivotType::LowestIndex);
    testDoNthElementUsingExample1WithPositiveAndNegativeIntegers<IntegerSelector, Integers>(selector);
}

TEST(QuickSelectorTest, GetNthSelectWorksOnCharactersUsingExample1) {
    CharacterSelector selector(PivotType::LowestIndex);
    testGetNthElementUsingExample1WithCharacters<CharacterSelector, Characters>(selector);
}

TEST(QuickSelectorTest, GetNthSelectWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegerSelector selector(PivotType::LowestIndex);
    testGetNthElementUsingExample1WithPositiveAndNegativeIntegers<IntegerSelector, Integers>(selector);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtLowestIndex) {
    CharacterSelector selector(PivotType::LowestIndex);
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToSort, 5);

    Characters valuesToExpect{'A', 'L', 'M', 'E', 'E', 'O', 'P', 'R', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtHighestIndex) {
    CharacterSelector selector(PivotType::HighestIndex);
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToSort, 5);

    Characters valuesToExpect{'E', 'A', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtRandomIndex) {
    CharacterSelector selector(PivotType::RandomIndex);
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToSort, 5);

    EXPECT_EQ('O', valuesToSort.at(5));
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtMedianOfMedians) {
    CharacterSelector selector(PivotType::MedianOfMedians);
    Characters valuesToSort{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToSort, 5);

    Characters valuesToExpect{'E', 'E', 'L', 'A', 'M', 'O', 'P', 'R', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToSort);
}

}  // namespace algorithm

}  // namespace alba
