#include <Algorithm/Sort/QuickSorter/QuickSelector.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSelector.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSelector;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Characters = vector<char>;
using Integers = vector<int>;
using CharacterSelector = QuickSelector<Characters>;
using IntegerSelector = QuickSelector<Integers>;
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1)
{
    CharacterSelector selector(PivotType::ValueAtLowestIndex);
    testDoNthElementUsingExample1WithCharacters<CharacterSelector, Characters>(selector);
}

TEST(QuickSelectorTest, DoNthSelectWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSelector selector(PivotType::ValueAtLowestIndex);
    testDoNthElementUsingExample1WithPositiveAndNegativeIntegers<IntegerSelector, Integers>(selector);
}

TEST(QuickSelectorTest, GetNthSelectWorksOnCharactersUsingExample1)
{
    CharacterSelector selector(PivotType::ValueAtLowestIndex);
    testGetNthElementUsingExample1WithCharacters<CharacterSelector, Characters>(selector);
}

TEST(QuickSelectorTest, GetNthSelectWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSelector selector(PivotType::ValueAtLowestIndex);
    testGetNthElementUsingExample1WithPositiveAndNegativeIntegers<IntegerSelector, Integers>(selector);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtLowestIndex)
{
    CharacterSelector selector(PivotType::ValueAtLowestIndex);
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToTest, 5U);

    Characters valuesToExpect{'A', 'L', 'M', 'E', 'E', 'O', 'P', 'R', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtHighestIndex)
{
    CharacterSelector selector(PivotType::ValueAtHighestIndex);
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToTest, 5U);

    Characters valuesToExpect{'E', 'A', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtRandomIndex)
{
    CharacterSelector selector(PivotType::ValueAtRandomIndex);
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToTest, 5U);

    EXPECT_EQ('O', valuesToTest.at(5U));
}

TEST(QuickSelectorTest, DoNthElementWorksOnCharactersUsingExample1WithPivotWithValueAtMedianOfMedians)
{
    CharacterSelector selector(PivotType::ValueAtMedianOfMedians);
    Characters valuesToTest{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};

    selector.doNthElement(valuesToTest, 5U);

    Characters valuesToExpect{'E', 'E', 'L', 'A', 'M', 'O', 'P', 'R', 'S', 'X', 'T'};
    EXPECT_EQ(valuesToExpect, valuesToTest);
}

}

}
