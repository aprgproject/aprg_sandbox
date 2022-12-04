#include <Algorithm/Sort/InsertionSorter/InsertionSorter.hpp>
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
using CharactersSorter = InsertionSorter<Characters>;
using ListOfCharactersSorter = InsertionSorter<ListOfCharacters>;
using IntegersSorter = InsertionSorter<Integers>;
using DoublesSorter = InsertionSorter<Doubles>;
using StringsSorter = InsertionSorter<Strings>;
using StabilityCheckObjectsSorter = InsertionSorter<StabilityCheckObjects>;
}

TEST(InsertionSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnListOfCharactersUsingExample1)
{
    ListOfCharactersSorter sorter;
    testSortUsingExample1WithCharacters<ListOfCharactersSorter, ListOfCharacters>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegersSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnDoublesUsingExample1)
{
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(InsertionSorterTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(InsertionSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckObjectsSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}

}
