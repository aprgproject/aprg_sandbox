#include <Algorithm/Sort/QuickSorter/QuickSorterWith3WayPartitioning.hpp>
#include <AlgorithmTests/Sort/Utilities/CommonTestsWithSorter.hpp>
#include <AlgorithmTests/Sort/Utilities/StabilityCheckObject.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSorter;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
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
}  // namespace

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingEmptyExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingOneValueExample) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingOneValueExampleWithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample2) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample2WithCharacters<CharactersSorter, Characters>(sorter);
}

// CANNOT SORT STD::LIST, actually it might be possible if we change indexes to iterators

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnPositiveAndNegativeIntegersUsingExample1) {
    IntegersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithPositiveAndNegativeIntegers<IntegersSorter, Integers>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnDoublesUsingExample1) {
    DoublesSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithDoubleValues<DoublesSorter, Doubles>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnStringsUsingExample1) {
    StringsSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithStrings<StringsSorter, Strings>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksAsNotStableOnStabilityCheckObjectsUsingExample1) {
    StabilityCheckObjectsSorter sorter(PivotType::LowestIndex);
    testSortAsNotStableUsingExample1WithStabilityCheckObjects<StabilityCheckObjectsSorter, StabilityCheckObjects>(
        sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtLowestIndex) {
    CharactersSorter sorter(PivotType::LowestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtHighestIndex) {
    CharactersSorter sorter(PivotType::HighestIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtRandomIndex) {
    CharactersSorter sorter(PivotType::RandomIndex);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

TEST(QuickSorterWith3WayPartitioningTest, SortWorksOnCharactersUsingExample1WithPivotWithValueAtMedianOfMedians) {
    CharactersSorter sorter(PivotType::MedianOfMedians);
    testSortUsingExample1WithCharacters<CharactersSorter, Characters>(sorter);
}

}  // namespace algorithm

}  // namespace alba
