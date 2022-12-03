#include <Algorithm/Sort/QuickSorter/QuickSorter.hpp>
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
using Doubles = vector<double>;
using Strings = vector<string>;
using StabilityCheckObjects = vector<StabilityCheckObject>;
using CharactersSorter = QuickSorter<Characters>;
using IntegersSorter = QuickSorter<Integers>;
using DoublesSorter = QuickSorter<Doubles>;
using StringsSorter = QuickSorter<Strings>;
using StabilityCheckObjectsSorter = QuickSorter<StabilityCheckObjects>;
}

TEST(QuickSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter;
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter;    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterTest, SortWorksOnCharactersUsingExample2){
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, actually it might be possible if we change indexes to iterators

TEST(QuickSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegersSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(QuickSorterTest, SortWorksOnDoublesUsingExample1)
{
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(QuickSorterTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(QuickSorterTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) // NOT STABLE
{
    StabilityCheckObjectsSorter sorter;
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}

}
