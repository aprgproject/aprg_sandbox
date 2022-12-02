#include <Algorithm/Sort/MergeSorter/TopDownMergeSorter.hpp>
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
using CharactersSorter = TopDownMergeSorter<Characters>;
using IntegersSorter = TopDownMergeSorter<Integers>;
using DoublesSorter = TopDownMergeSorter<Doubles>;
using StringsSorter = TopDownMergeSorter<Strings>;
using StabilityCheckObjectsSorter = TopDownMergeSorter<StabilityCheckObjects>;
}

TEST(TopDownMergeSorterTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter;
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter;
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(TopDownMergeSorterTest, SortWorksOnCharactersUsingExample2)
{
    CharactersSorter sorter;
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST

TEST(TopDownMergeSorterTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegersSorter sorter;
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(TopDownMergeSorterTest, SortWorksOnDoublesUsingExample1)
{
    DoublesSorter sorter;
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(TopDownMergeSorterTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter;
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(TopDownMergeSorterTest, SortWorksAsStableOnStabilityCheckObjectsUsingExample1) // STABLE
{
    StabilityCheckObjectsSorter sorter;
    testSortAsStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

}

}
