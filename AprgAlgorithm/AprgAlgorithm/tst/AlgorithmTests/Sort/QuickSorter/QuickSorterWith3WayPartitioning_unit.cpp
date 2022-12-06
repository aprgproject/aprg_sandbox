#include <Algorithm/Sort/QuickSorter/QuickSorterWith3WayPartitioning.hpp>
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
using CharactersSorter = QuickSorterWith3WayPartitioning<Characters>;
using IntegersSorter = QuickSorterWith3WayPartitioning<Integers>;
using DoublesSorter = QuickSorterWith3WayPartitioning<Doubles>;
using StringsSorter = QuickSorterWith3WayPartitioning<Strings>;
using StabilityCheckObjectsSorter = QuickSorterWith3WayPartitioning<StabilityCheckObjects>;
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample)
{
    CharactersSorter sorter(PivotType::ValueAtLowestIndex);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingOneValueExample)
{
    CharactersSorter sorter(PivotType::ValueAtLowestIndex);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1)
{
    CharactersSorter sorter(PivotType::ValueAtLowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample2)
{
    CharactersSorter sorter(PivotType::ValueAtLowestIndex);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, actually it might be possible if we change indexes to iterators

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1)
{
    IntegersSorter sorter(PivotType::ValueAtLowestIndex);
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnDoublesUsingExample1)
{
    DoublesSorter sorter(PivotType::ValueAtLowestIndex);
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnStringsUsingExample1)
{
    StringsSorter sorter(PivotType::ValueAtLowestIndex);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) // NOT STABLE
{
    StabilityCheckObjectsSorter sorter(PivotType::ValueAtLowestIndex);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtLowestIndex)
{
    CharactersSorter sorter(PivotType::ValueAtLowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtHighestIndex)
{
    CharactersSorter sorter(PivotType::ValueAtHighestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtRandomIndex)
{
    CharactersSorter sorter(PivotType::ValueAtRandomIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtMedianOfMedians)
{
    CharactersSorter sorter(PivotType::ValueAtMedianOfMedians);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

}

}
