#include <Algorithm/Sort/SelectionSorter.hpp>
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
using CharacterSorter = SelectionSorter<Characters>;
using IntegerSorter = SelectionSorter<Integers>;
using StringSorter = SelectionSorter<Strings>;
using StabilityCheckSorter = SelectionSorter<StabilityCheckObjects>;
}
TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharacterSorter sorter;    testSortUsingExample1WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharacterSorter sorter;
    testSortUsingExample2WithCharacters<CharacterSorter, Characters>(sorter);
}

TEST(SelectionSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegerSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegerSorter, Integers>(sorter);
}

TEST(SelectionSorterTest, SortWorksOnStringsUsingExample1)
{
    StringSorter sorter;
    testSortUsingExample1WithStrings<StringSorter, Strings>(sorter);
}

TEST(SelectionSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1)
{
    StabilityCheckSorter sorter;    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckSorter, StabilityCheckObjects>(sorter);
}

}
}
