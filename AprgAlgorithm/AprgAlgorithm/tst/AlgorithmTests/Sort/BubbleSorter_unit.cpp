#include <Algorithm/Sort/BubbleSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Characters = vector<char>;
using Integers = vector<int>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharacterSorter = BubbleSorter<Characters>;
using IntegerSorter = BubbleSorter<Integers>;
using StringSorter = BubbleSorter<Strings>;
using StabilityCheckSorter = BubbleSorter<StabilityCheckObjects>;
}
TEST(BubbleSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter;    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(BubbleSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter;
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(BubbleSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>(sorter);
}

TEST(BubbleSorterTest, SortWorksOnStringsUsingExample1)
{
    StringSorter sorter;
    testSortUsingExample1WithStrings<StringSorter, Strings>(sorter);
}

TEST(BubbleSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckSorter sorter;    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}
}
