#include <Algorithm/Sort/SelectionSorter/SelectionSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

#include <list>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Characters = vector<char>;
using ListOfCharacters = list<char>;
using Integers = vector<int>;
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = SelectionSorter<Characters>;
using ListOfCharactersSorter = SelectionSorter<ListOfCharacters>;
using IntegersSorter = SelectionSorter<Integers>;
using DoublesSorter = SelectionSorter<Doubles>;
using StringsSorter = SelectionSorter<Strings>;
using StabilityCheckObjectsSorter = SelectionSorter<StabilityCheckObjects>;
}

TEST(SelectionSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(SelectionSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(SelectionSorterTest, SortWorksOnListOfCharactersUsingExample1)
{
    ListOfCharactersSorter sorter;
    testSortUsingExample1WithCharacters<ListOfCharactersSorter, ListOfCharacters>(sorter);
}

TEST(SelectionSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegersSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(SelectionSorterTest, SortWorksOnDoublesUsingExample1)
{
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(SelectionSorterTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(SelectionSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckObjectsSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}

}
