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
    CharacterSelector selector;
    testDoNthElementUsingExample1WithCharacters<CharacterSelector, Characters>(selector);
}

TEST(QuickSelectorTest, DoNthSelectWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSelector selector;
    testDoNthElementUsingExample1WithPositiveAndNegativeIntegers<IntegerSelector, Integers>(selector);
}

TEST(QuickSelectorTest, GetNthSelectWorksOnCharactersUsingExample1)
{
    CharacterSelector selector;
    testGetNthElementUsingExample1WithCharacters<CharacterSelector, Characters>(selector);
}

TEST(QuickSelectorTest, GetNthSelectWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSelector selector;
    testGetNthElementUsingExample1WithPositiveAndNegativeIntegers<IntegerSelector, Integers>(selector);
}

}

}
